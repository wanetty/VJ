﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenLvl : MonoBehaviour {

    public GameObject Agua;
    public GameObject Hierba;
    public GameObject Carretera;
    public GameObject CarreteraDoble;
    public GameObject CarreteraTriple;
    public GameObject NoPisarHierba;
    public GameObject Arbol2;
    public GameObject Arbol3;
    public GameObject Arbol4;
    public GameObject Arbol5;


    int primero, segundo;
    int display = 12*40;
    bool carreterasimple = false;
    bool carreteradoble = false;

    Vector3 intPos = new Vector3(0, 0, 0);
    Vector3 intPosArbol = new Vector3(0, 0, 0);


    // Update is called once per frame
    void Update () {
        if (Input.GetButtonDown("arriba")) {
            primero = Random.Range(1, 4);
            if (primero == 1) //pintamos tierra 
            {
                carreteradoble = carreterasimple = false;
                segundo = Random.Range(1, 4);
                for (int i = 0; i < segundo; ++i)
                {
                    intPos = new Vector3(0, 0.4f, display);
                    int numArboles = Random.Range(1, 4);
                    int posArboles;
                    for (int j = 0; j < numArboles; ++j)
                    { 
                        posArboles = Random.Range(-4, 5);
                        intPosArbol = new Vector3(posArboles * 40, 25, display);
                        GameObject ArbolInst = Instantiate(Arbol4) as GameObject;
                        ArbolInst.transform.position = intPosArbol;
                    }//Arboles.
                    display += 40;
                    GameObject HierbaIns = Instantiate(Hierba) as GameObject;
                    GameObject NoHierbaIns = Instantiate(NoPisarHierba) as GameObject;
                    HierbaIns.transform.position = intPos;
                    NoHierbaIns.transform.position = intPos;

                }
            }
            if (primero == 2) //pintamos carrertera
            {
                segundo = Random.Range(1, 3);
                if(segundo == 1 && !carreterasimple && !carreteradoble)
                {
                    carreterasimple = true;
                    intPos = new Vector3(0, 0.2f, display);
                    display += 40;
                    GameObject CarreteraIns = Instantiate(Carretera) as GameObject;
                    CarreteraIns.transform.position = intPos;
                } else if(segundo == 2 && !carreterasimple && !carreteradoble)
                {
                    carreteradoble = true;
                    intPos = new Vector3(0, 0.2f, display+20);
                    display += 80;
                    GameObject CarreteraIns = Instantiate(CarreteraDoble) as GameObject;
                    CarreteraIns.transform.position = intPos;
                }
                
                /*for (int i = 0; i < segundo; ++i)
                {

                    intPos = new Vector3(0, -0.1f, display);
                    display += 40;
                    GameObject CarreteraIns = Instantiate(Carretera) as GameObject;
                    CarreteraIns.transform.position = intPos;
                }*/
            }
            if (primero == 3)
            {
                carreteradoble = carreterasimple = false;
                segundo = Random.Range(1, 4);
                for (int i = 0; i < segundo; ++i)
                {
                    intPos = new Vector3(0, -0.1f, display);
                    display += 40;
                    GameObject AguaIns = Instantiate(Agua) as GameObject;
                    AguaIns.transform.position = intPos;
                }
            }

        }
            
	}
}
