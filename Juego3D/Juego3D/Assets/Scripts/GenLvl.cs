using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenLvl : MonoBehaviour {

    public GameObject Agua;
    public GameObject Hierba;
    public GameObject CarreteraF;
    public GameObject CarreteraM;
    public GameObject CarreteraD;
    public GameObject CarreteraDF;
    public GameObject CarreteraDM;
    public GameObject CarreteraDD;
    public GameObject CarreteraTF;
    public GameObject CarreteraTM;
    public GameObject CarreteraTD;
    public GameObject Arbol2;
    public GameObject Arbol3;
    public GameObject Arbol4;
    public GameObject Arbol5; 
    

    int primero, segundo ,tipoArbol;
    public int display;
    bool carreteradoble = false;
    int posJugadorZ;

    Vector3 intPos = new Vector3(0, 0, 0);
    Vector3 intPosArbol = new Vector3(0, 0, 0);
    Vector3 intPosArbolNoPisar1 = new Vector3(0, 0, 0);
    Vector3 intPosArbolNoPisar2 = new Vector3(0, 0, 0);


    // Update is called once per frame
    void Update () {
        GameObject jugador = GameObject.Find("gallina");
        GameObject[] Arboles = new GameObject[4] { Arbol2, Arbol3, Arbol4, Arbol5 };
        if (Input.GetButtonDown("arriba") && (jugador.transform.position.z+560) > display ) {
            primero = Random.Range(1, 4);
            if (primero == 1) //pintamos tierra 
            {
                carreteradoble  = false; // Se pone a falso, ya que no es una carreta
                segundo = Random.Range(1, 4);
                for (int i = 0; i < segundo; ++i)
                {
                    intPos = new Vector3(0, 0.4f, display);
                    int numArboles = Random.Range(1, 4); // Se calcula cantidad de arboles máximos por hierba
                    int posArboles;
                    GameObject ArbolInst;
                    for (int j = 0; j < numArboles; ++j) // Pone los arboles sobre la hierba.
                    { 
                        posArboles = Random.Range(-4, 5); // Se calcula la posicion de los arboles
                        intPosArbol = new Vector3(posArboles * 40, 25, display); 
                        tipoArbol = Random.Range(0, 4);
                        ArbolInst = Instantiate(Arboles[tipoArbol]) as GameObject;
                        ArbolInst.transform.position = intPosArbol;
                    }//Arboles.
                    
                    GameObject HierbaIns = Instantiate(Hierba) as GameObject; //Instacia hierba que si se puede 
                    HierbaIns.transform.position = intPos;
                    //Agregamos arboles a la hierba que no se pisa.
                    intPosArbolNoPisar1 = new Vector3(-200,25, display);
                    intPosArbolNoPisar2 = new Vector3(200, 25, display);
                    ArbolInst = Instantiate(Arboles[tipoArbol]) as GameObject;
                    ArbolInst.transform.position = intPosArbolNoPisar1; //Posiciono primer Arbol.
                    ArbolInst = Instantiate(Arboles[tipoArbol]) as GameObject;
                    ArbolInst.transform.position = intPosArbolNoPisar2; //Posiciono segundo Arbol.
                    display += 40; //El display le sumamos 40


                }
            }
            if (primero == 2) //pintamos carrertera
            {
                segundo = Random.Range(1, 4);
                if(segundo == 1  && !carreteradoble)// nos evita poner una carretera si hay otra porque las lineas no coinciden.
                {
                    carreteradoble = true;
                    intPos = new Vector3(0, 0.2f, display);
                    display += 40;
                    GameObject CarreteraIns = Instantiate(CarreteraF) as GameObject;
                    CarreteraIns.transform.position = intPos;
                } else if(segundo == 2 && !carreteradoble)
                {
                    carreteradoble = true;
                    intPos = new Vector3(0, 0.2f, display+20);
                    display += 80;
                    GameObject CarreteraIns = Instantiate(CarreteraDF) as GameObject;
                    CarreteraIns.transform.position = intPos;
                }
                else if (segundo == 3 && !carreteradoble)
                {
                    carreteradoble = true;
                    intPos = new Vector3(0, 0.2f, display + 40);
                    display += 120;
                    GameObject CarreteraIns = Instantiate(CarreteraTF) as GameObject;
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
                carreteradoble = false;
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

    private void genArboles()
    {

    }
}
