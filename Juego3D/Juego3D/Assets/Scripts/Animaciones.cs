using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Animaciones: MonoBehaviour {
    bool perdido;
    float time;
	
    void Start()
    {
        perdido = false;
        time = 0;
    }
	// Update is called once per frame
	void Update () {
        time += Time.deltaTime;
        if (!perdido && time > 0.2)
        {
            if (Input.GetButtonDown("izq"))
            {
                time = 0;
                gameObject.transform.rotation = Quaternion.Euler(0, 90, 0);
            }
            if (Input.GetButtonDown("der"))
            {
                time = 0;
                gameObject.transform.rotation = Quaternion.Euler(0, -90, 0);
            }
            if (Input.GetButtonDown("arriba"))
            {
                time = 0;
                gameObject.transform.rotation = Quaternion.Euler(0, 0, 0);
            }
            if (Input.GetButtonDown("abajo"))
            {
                time = 0;
                gameObject.transform.rotation = Quaternion.Euler(0, 180, 0);
            }
        }
    }

    public void setPerdido()
    {
        perdido = true;
    }
}
