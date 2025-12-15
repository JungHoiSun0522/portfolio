using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using SockErrorCode; //SocketException의 에러 코드를 정리한 소스 파일
                     //해당 코드와 내용은 아래 링크에서 가지고 옴
                     //https://learn.microsoft.com/ko-kr/windows/win32/winsock/windows-sockets-error-codes-2
namespace Client
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private Socket client;
        private IPEndPoint ep;
        private Thread thread;
        bool m_bRun = false;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void AddChatMessage(string msg)
        {
            lstChat.Items.Add(msg); //리스트 박스에 아이템을 추가하고
            lstChat.UpdateLayout(); //목록을 업데이트함

            var lastItem = lstChat.Items[lstChat.Items.Count - 1]; //마지막 아이템의 인덱스를 저장하고
            lstChat.ScrollIntoView(lastItem); //해당 인덱스로 스크롤을 움직여 메세지가 쌓여도 마지막 인덱스에 머무름
        }

        private void SendToServer(string msg)
        {
            byte[] buff = Encoding.UTF8.GetBytes(msg); //서버로 보낼 메세지를 UTF-8로 인코딩.
            client.Send(buff);
        }

        private void ServerReceive()
        {
            client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 52345); //접속할 서버의 주소와 포트

            try
            {
                client.Connect(ep);

                Dispatcher.Invoke(() => //워커 쓰레드에서 UI쓰레드에 직접 접근이 안 되므로 Dispatcher를 이용하여 요청
                {
                    AddChatMessage("연결 성공.");
                    AddChatMessage("사용자가 입장하였습니다.");
                });
                m_bRun = true; //서버로 부터 메세지를 수신하기 위한 플래그

                while (m_bRun)
                {
                    byte[] buff = new byte[8192];

                    int n = client.Receive(buff);
                    string msg = string.Empty;

                    if (n == 0)
                        continue;

                    if (Encoding.UTF8.GetString(buff, 0, n) == "상대가 입장하였습니다."   //타 클라이언트의 입장과 퇴장을                
                        || Encoding.UTF8.GetString(buff, 0, n) == "상대가 떠났습니다.")  //알리기 위한 메세지를 리시브함
                        msg = Encoding.UTF8.GetString(buff, 0, n);
                    else
                        msg = "[상대] : " + Encoding.UTF8.GetString(buff, 0, n);


                    Dispatcher.Invoke(() => AddChatMessage(msg));
                }
            }
            catch (SocketException se)
            {
                int code = se.ErrorCode;
                string msg = SocketErrorCode.SearchCode(code); //SocketException의 에러 코드를
                                                               //딕셔너리로 정리한 파일(SockErrorCode.cs)에서 불러옴
                if (msg != "")
                    Dispatcher.Invoke(() => AddChatMessage(msg));
            }
            catch (ObjectDisposedException)
            {
                Dispatcher.Invoke(() => AddChatMessage("연결이 종료되었습니다."));
            }
            catch (Exception e)
            {
                Dispatcher.Invoke(() => AddChatMessage("예외 : " + e.Message));
            }
            finally
            {

                try { client?.Close(); } catch { }
                try { client?.Dispose(); } catch { }
                client = null;

                Dispatcher.Invoke(() =>
                {
                    btnDisconnect.IsEnabled = false;
                    btnConnect.IsEnabled = true;
                    btnSend.IsEnabled = false;
                });

                m_bRun = false; //서버와의 통신이 끊어짐에 따라 초기화
            }
        }

        private void btnConnect_Click(object sender, RoutedEventArgs e)
        {
            if (!m_bRun)
            {
                AddChatMessage("연결 중 . . .");
                thread = new Thread(ServerReceive);
                thread.IsBackground = true;
                thread.Start();
                //서버 접속과 접속 해제, 전송 버튼의 활성 및 비활성
                btnDisconnect.IsEnabled = true;
                btnConnect.IsEnabled = false;
                btnSend.IsEnabled = true;
            }
        }

        private void btnDisconnect_Click(object sender, RoutedEventArgs e)
        {
            if (!m_bRun) //서버와 연결된 게 아니면 리턴
                return;

            m_bRun = false;

            try
            {
                client?.Shutdown(SocketShutdown.Both);
                client?.Close();
                client?.Dispose();
                ep = null;
            }
            catch { }

            AddChatMessage("접속 해제");
            btnDisconnect.IsEnabled = false;
            btnConnect.IsEnabled = true;
            btnSend.IsEnabled = false;
        }

        private void btnSend_Click(object sender, RoutedEventArgs e)
        {
            string msg = "[나] : ";
            msg += txtMessage.Text;
            SendToServer(txtMessage.Text);
            AddChatMessage(msg);
            txtMessage.Clear();
        }

        private void TextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == System.Windows.Input.Key.Enter)
            {
                if (!m_bRun || txtMessage.Text == "") //서버와 연결된 게 아니거나 공백이면 리턴
                    return;

                string msg = "[나] : ";
                msg += txtMessage.Text;
                SendToServer(txtMessage.Text);
                AddChatMessage(msg);
                txtMessage.Clear();
            }
        }
    }
}
