using System;
using System.Collections.Generic;

namespace SockErrorCode
{
    class SocketErrorCode
    {
        static private Dictionary<int, string> errorcode = new Dictionary<int, string>()
        {
            { 6, "SocketException : 지정된 이벤트 개체 핸들이 잘못되었습니다." },
            { 87, "SocketException : 하나 이상의 매개 변수가 잘못되었습니다."},
            { 995, "SocketException : 겹치는 작업이 중단되었습니다." },
            { 996, "SocketException : 겹치는 I/O 이벤트 개체가 신호 상태가 아닙니다." },
            //{ 10004, "SocketException : 함수 호출이 중단되었습니다." }, //정상 종료임에도 반복적으로 출려되어 주석 처리함.
            { 10013, "SocketException : 사용 권한이 거부되었습니다." },
            { 10014, "SocketException : 잘못된 주소입니다." },
            { 10022, "SocketException : 인수가 잘못되었습니다." },
            { 10024, "SocketException : 열린 소켓이 너무 많습니다." },
            { 10035, "SocketException : 리소스를 일시적으로 사용할 수 없습니다." },
            { 10038, "SocketException : nonsocket에 대한 소켓 작업입니다." },
            { 10039, "SocketException : 대상 주소가 필요합니다." },
            { 10040, "SocketException : 메시지가 너무 깁니다." },
            { 10041, "SocketException : 소켓의 프로토콜 유형이 잘못되었습니다." },
            { 10042, "SocketException : 잘못된 프로토콜 옵션입니다." },
            { 10043, "SocketException : 프로토콜이 지원되지 않습니다." },
            { 10044, "SocketException : 소켓 유형이 지원되지 않습니다." },
            { 10045, "SocketException : 작업이 지원되지 않습니다." },
            { 10046, "SocketException : 프로토콜 패밀리는 지원되지 않습니다." },
            { 10047, "SocketException : 프로토콜 패밀리에서 지원되지 않는 주소 패밀리입니다." },
            { 10048, "SocketException : 이미 사용 중인 주소입니다." },
            { 10049, "SocketException : 요청된 주소를 할당할 수 없습니다." },
            { 10050, "SocketException : 네트워크가 다운되었습니다." },
            { 10051, "SocketException : 네트워크에 연결할 수 없습니다." },
            { 10052, "SocketException : 다시 설정할 때 네트워크 연결이 끊어지게 됩니다." },
            { 10053, "SocketException : 소프트웨어로 인해 연결이 중단되었습니다." },
            { 10054, "SocketException : 현재 연결은 원격 호스트에 의해 강제로 끊겼습니다." },
            { 10055, "SocketException : 사용할 수 있는 버퍼 공간이 없습니다." },
            { 10056, "SocketException : 소켓이 이미 연결되어 있습니다." },
            { 10057, "SocketException : 소켓이 연결되어 있지 않습니다." },
            { 10058, "SocketException : 소켓 종료 후에는 보낼 수 없습니다." },
            { 10059, "SocketException : 참조가 너무 많습니다." },
            { 10060, "SocketException : 연결 시간이 초과되었습니다." },
            { 10061, "SocketException : 연결이 거부되었습니다." },
            { 10062, "SocketException : 이름을 번역할 수 없습니다." },
            { 10064, "SocketException : 호스트가 다운되었습니다." },
            { 10065, "SocketException : 호스트할 경로가 없습니다." },
            { 10066, "SocketException : 디렉터리가 비어 있지 않습니다." },
            { 10067, "SocketException : 프로세스가 너무 많습니다." },
            { 10068, "SocketException : 사용자 할당량을 초과했습니다." },
            { 10069, "SocketException : 디스크 할당량을 초과했습니다." },
            { 10070, "SocketException : 부실 파일 핸들 참조입니다." },
            { 10071, "SocketException : 항목이 원격입니다. 항목을 로컬로 사용할 수 없습니다." },
            { 10091, "SocketException : 네트워크 하위 시스템을 사용할 수 없습니다." },
            { 10092, "SocketException : Winsock.dll 버전이 범위를 벗어났습니다." },
            { 10093, "SocketException : WSAStartup이 아직 수행되지 않았습니다." },
            { 10102, "SocketException : 더 이상 결과가 없습니다." },
            { 10103, "SocketException : 통화가 취소되었습니다." },
            { 10104, "SocketException : 프로시저 호출 테이블이 잘못되었습니다." },
            { 10105, "SocketException : 서비스 공급자가 잘못되었습니다." },
            { 10106, "SocketException : 서비스 공급자를 초기화하지 못했습니다." },
            { 10107, "SocketException : 시스템 호출 실패." },
            { 10108, "SocketException : 서비스를 찾을 수 없습니다." },
            { 10109, "SocketException : 클래스 형식을 찾을 수 없습니다." },
            { 10110, "SocketException : 더 이상 결과가 없습니다." },
            { 11001, "SocketException : 호스트를 찾을 수 없습니다." },
            { 11002, "SocketException : 인증되지 않은 호스트를 찾을 수 없습니다." },
            { 11003, "SocketException : 복구할 수 없는 오류입니다." },
            { 11004, "SocketException : 유효한 이름이며 요청된 형식의 데이터 레코드가 없습니다." },
            { 11007, "SocketException : QoS 보낸 사람이 없습니다." },
            { 11008, "SocketException : QoS 수신자가 없습니다." },
            { 11010, "SocketException : QoS 허용 오류입니다." },
            { 11011, "SocketException : QoS 정책 실패." },
            { 11012, "SocketException : QoS 잘못된 스타일입니다." },
            { 11013, "SocketException : QoS 잘못된 개체입니다." },
            { 11014, "SocketException : QoS 트래픽 제어 오류입니다." },
            { 11015, "SocketException : QoS 제네릭 오류입니다." },
            { 11016, "SocketException : QoS 서비스 유형 오류입니다." },
            { 11017, "SocketException : QoS flowspec 오류입니다." },
            { 11018, "SocketException : QoS 공급자 버퍼가 잘못되었습니다." },
            { 11019, "SocketException : QoS 필터 스타일이 잘못되었습니다." },
            { 11020, "SocketException : QoS 필터 형식이 잘못되었습니다." },
            { 11021, "SocketException : 잘못된 QoS 필터 수입니다." },
            { 11022, "SocketException : QoS 개체 길이가 잘못되었습니다." },
            { 11023, "SocketException : 잘못된 QoS 흐름 수입니다." },
            { 11024, "SocketException : 인식할 수 없는 QoS 개체입니다." },
            { 11025, "SocketException : 잘못된 QoS 정책 개체입니다." },
            { 11026, "SocketException : 잘못된 QoS 흐름 설명자입니다." },
            { 11027, "SocketException : QoS 공급자별 flowspec이 잘못되었습니다." },
            { 11028, "SocketException : QoS 공급자별 filterspec이 잘못되었습니다." },
            { 11029, "SocketException : 잘못된 QoS 셰이프 삭제 모드 개체입니다." },
            { 11030, "SocketException : QoS 셰이핑 속도 개체가 잘못되었습니다." },
            { 11031, "SocketException : 예약된 정책 QoS 요소 형식입니다." }
        };

        static public string SearchCode(int code)
        {
            if (!errorcode.ContainsKey(code))
                return "";
            return errorcode[code];
        }
    }

}