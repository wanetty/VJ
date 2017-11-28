using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenLvl : MonoBehaviour {

    public GameObject Agua;
    public GameObject Hierba;
    public GameObject Carretera;

    int primero, segundo;
    int display = 12;

    Vector3 intPos = new Vector3(0, 0, 0);
	
	// Update is called once per frame
	void Update () {
        if (Input.GetButtonDown("arriba")) {
            primero = Random.Range(1, 4);
            if (primero == 1) 
            {
                segundo = Random.Range(1, 4);
                for (int i = 0; i < segundo; ++i)
                {
                    intPos = new Vector3(0, 0, display);
                    display += 1;
                    GameObject HierbaIns = Instantiate(Hierba) as GameObject;
                    HierbaIns.transform.position = intPos;
                }
            }
            if (primero == 2)
            {
                segundo = Random.Range(1, 4);
                for (int i = 0; i < segundo; ++i)
                {
                    intPos = new Vector3(0, -0.1f, display);
                    display += 1;
                    GameObject CarreteraIns = Instantiate(Carretera) as GameObject;
                    CarreteraIns.transform.position = intPos;
                }
            }
            if (primero == 3)
            {
                segundo = Random.Range(1, 4);
                for (int i = 0; i < segundo; ++i)
                {
                    intPos = new Vector3(0, -0.1f, display);
                    display += 1;
                    GameObject AguaIns = Instantiate(Agua) as GameObject;
                    AguaIns.transform.position = intPos;
                }
            }

        }
            
	}
}
