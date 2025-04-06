using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightBlink : MonoBehaviour
{
	private Light theLight;
	private float targetIntensity;
	private float currentIntensity;
	float intensity;
	float LightTime;
	
    private void Start()
    {
		theLight = GetComponent<Light>();
		intensity = theLight.intensity;
		currentIntensity = theLight.intensity;
		targetIntensity = Random.Range(0.4f, 1f);
		LightTime = 10f;
    }

    void Update()
    {
		if (LightTime > 0)
		{
			if (Mathf.Abs(targetIntensity - currentIntensity) >= 0.01)
			{
				if ((targetIntensity - currentIntensity) >= 0)
					currentIntensity += Time.deltaTime * 3f;
				else
					currentIntensity -= Time.deltaTime * 3f;

				theLight.intensity = currentIntensity;
				theLight.range = currentIntensity + 10;
				LightTime -= Time.deltaTime;
			}
			else
			{
				targetIntensity = Random.Range(0.4f, 1f);
				LightTime -= Time.deltaTime;
			}
		}
		else
        {
			LightTime = 0;
			theLight.range = 10;
			theLight.intensity = intensity;
        }
    }
}
