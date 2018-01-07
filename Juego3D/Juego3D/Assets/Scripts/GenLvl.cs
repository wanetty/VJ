using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenLvl : MonoBehaviour {

    public GameObject RioF;
    public GameObject RioM;
    public GameObject RioD;
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
    public int difmin, difmax;
    public int maxArboles;

    private GameObject jugador;
    private GameObject[] Arboles;
    private GameObject[] Carreteras;
    private GameObject[] CDobles;
    private GameObject[] CTriples;
    private GameObject[] Rios;
    private Animator MovsAgua;
    private Animation Animplanta;
    int tipoVia, numVias ,tipoArbol, tipoxDif;
    public int display;
    bool carretera = false;
    int posJugadorZ;

    Vector3 intPos = new Vector3(0, 0, 0);
    Vector3 intPosArbol = new Vector3(0, 0, 0);
    Vector3 intPosArbolNoPisar1 = new Vector3(0, 0, 0);
    Vector3 intPosArbolNoPisar2 = new Vector3(0, 0, 0);
    
    void Start()
    {
        jugador = GameObject.Find("gallina");
        Arboles = new GameObject[4] { Arbol2, Arbol3, Arbol4, Arbol5 };
        Carreteras = new GameObject[3] { CarreteraF, CarreteraM,  CarreteraD };
        CDobles = new GameObject[3] { CarreteraDF,  CarreteraDM,  CarreteraDD };
        CTriples = new GameObject[3] { CarreteraTF,  CarreteraTM, CarreteraTD  };
        Rios = new GameObject[3] { RioF, RioM,RioD};
        MovsAgua = GameObject.FindGameObjectWithTag("Agua/corriente").GetComponent<Animator>();
        Animplanta = GameObject.FindGameObjectWithTag("Planta").GetComponent<Animation>();
        difmax = 2;
        difmin = 1;
    }

    // Update is called once per frame
    void Update () {

        MovsAgua.Play("MovAgua");
        Animplanta.Play("girar");
        if (Input.GetButtonDown("arriba") && (jugador.transform.position.z+560) > display ) {
            tipoVia = Random.Range(1, 4);
            if (tipoVia == 1) //pintamos tierra 
            {
                carretera  = false; // Se pone a falso, ya que no es una carreta
                numVias = Random.Range(1, 4);
                for (int i = 0; i < numVias; ++i)
                {
                    intPos = new Vector3(0, 0.4f, display);
                    int numArboles = Random.Range(1, maxArboles); // Se calcula cantidad de arboles máximos por hierba
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
                    ArbolInst = Instantiate(Arboles[tipoArbol]) as GameObject;
                    ArbolInst.transform.position = intPosArbolNoPisar1; //Posiciono primer Arbol.
                    ArbolInst = Instantiate(Arboles[tipoArbol]) as GameObject;
                    ArbolInst.transform.position = intPosArbolNoPisar2; //Posiciono segundo Arbol.
                    display += 40; //El display le sumamos 40


                }
            }
            if (tipoVia == 2) //pintamos carrertera
            {
                numVias = Random.Range(1, 4);
                if(numVias == 1  && !carretera)// nos evita poner una carretera si hay otra porque las lineas no coinciden.
                {
                    carretera = true;
                    intPos = new Vector3(0, 0.2f, display);
                    display += 40;
                    tipoxDif = Random.Range(difmin,difmax);
                    GameObject CarreteraIns = Instantiate(Carreteras[tipoxDif]) as GameObject;
                    CarreteraIns.transform.position = intPos;
                } else if(numVias == 2 && !carretera)
                {
                    carretera = true;
                    intPos = new Vector3(0, 0.2f, display+20);
                    display += 80;
                    tipoxDif = Random.Range(difmin, difmax);
                    GameObject CarreteraIns = Instantiate(CDobles[tipoxDif]) as GameObject;
                    CarreteraIns.transform.position = intPos;
                }
                else if (numVias == 3 && !carretera)
                {
                    carretera = true;
                    intPos = new Vector3(0, 0.2f, display + 40);
                    display += 120;
                    tipoxDif = Random.Range(difmin, difmax);
                    GameObject CarreteraIns = Instantiate(CTriples[tipoxDif]) as GameObject;
                    CarreteraIns.transform.position = intPos;
                }
            }
            if (tipoVia == 3)
            {
                carretera = false;
                numVias = Random.Range(1, 4);
                for (int i = 0; i < numVias; ++i)
                {
                    intPos = new Vector3(0, -0.1f, display);
                    tipoxDif = Random.Range(difmin, difmax);
                    GameObject AguaIns = Instantiate(Rios[tipoxDif]) as GameObject;
                    AguaIns.transform.position = intPos;
                    display += 40;
                }
            }

        }
            
	}

    private void genArboles()
    {

    }
}
