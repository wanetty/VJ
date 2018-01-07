using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenLvl : MonoBehaviour {

    public GameObject RioF;
    public GameObject RioM;
    public GameObject RioD;
    public GameObject RioSeco;
    public GameObject planta;
    public GameObject Hierba;
    public GameObject CarreteraF;
    public GameObject CarreteraF2;
    public GameObject CarreteraM;
    public GameObject CarreteraD;
    public GameObject CarreteraDF;
    public GameObject CarreteraDM;
    public GameObject CarreteraDM2;
    public GameObject CarreteraDD;
    public GameObject CarreteraDD2;
    public GameObject CarreteraTF;
    public GameObject CarreteraTM;
    public GameObject CarreteraTM2;
    public GameObject CarreteraTD;
    public GameObject Tren;
    public GameObject Arbol2;
    public GameObject Arbol3;
    public GameObject Arbol4;
    public GameObject Arbol5;
    public GameObject Roca1;
    public GameObject Roca2;
    public GameObject Moneda;
    public int difmin, difmax;
    public int maxArboles;

    private GameObject jugador;
    private GameObject[] Arboles;
    private GameObject[] Carreteras;
    private GameObject[] CDobles;
    private GameObject[] CTriples;
    private GameObject[] Rios;
    private Animator MovsAgua;
    private Animator AnimMoneda;
    private Animation Animplanta;
    int tipoVia, numVias ,tipoArbol, tipoxDif;
    public int display;
    bool hayplantas;
    bool carretera = false;
    int posJugadorZ;

    Vector3 intPos = new Vector3(0, 0, 0);
    Vector3 intPosArbol = new Vector3(0, 0, 0);
    Vector3 intPosArbolNoPisar1 = new Vector3(0, 25, 0);
    Vector3 intPosArbolNoPisar2 = new Vector3(0, 25, 0);
    
    void Start()
    {
        jugador = GameObject.Find("gallina");
        Arboles = new GameObject[6] { Arbol2, Arbol3, Arbol4, Arbol5, Roca1, Roca2 };
        Carreteras = new GameObject[3] { CarreteraF, CarreteraM,  CarreteraD };
        CDobles = new GameObject[3] { CarreteraDF,  CarreteraDM,  CarreteraDD };
        CTriples = new GameObject[3] { CarreteraTF,  CarreteraTM, CarreteraTD  };
        Rios = new GameObject[3] { RioF, RioM,RioD};
        hayplantas = false;
        difmax = 1;
        difmin = 0;
    }

    // Update is called once per frame
    void Update () {
        

        if ((jugador.transform.position.z+560) > display ) {
            tipoVia = Random.Range(1, 5);
            if (tipoVia == 1) //pintamos tierra 
            {
                carretera  = false; // Se pone a falso, ya que no es una carreta
                numVias = Random.Range(1, 4);
                List<int> posicionesZ = new List<int>();
                for (int i = 0; i < numVias; ++i)
                {
                    intPos = new Vector3(0, 0.4f, display);
                    int numArboles = Random.Range(1, maxArboles); // Se calcula cantidad de arboles máximos por hierba
                    int posArboles;
                    GameObject ArbolInst;
                    for (int j = 0; j < numArboles; ++j) // Pone los arboles sobre la hierba.
                    { 
                        posArboles = Random.Range(-4, 5); // Se calcula la posicion de los arboles
                        if (!posicionesZ.Contains(posArboles))
                        {
                            posicionesZ.Add(posArboles);
                            intPosArbol = new Vector3(posArboles * 40, 25, display);
                            tipoArbol = Random.Range(0, 6);
                            ArbolInst = Instantiate(Arboles[tipoArbol]) as GameObject;
                            ArbolInst.transform.position = intPosArbol;
                        }
                    }//Arboles.
                    if (Random.Range(1, 11) == 10)
                    {
                        
                        bool posicionada = false;
                        while (!posicionada)
                        {
                            int PosMoneda = Random.Range(-4, 5);
                            if (!posicionesZ.Contains(PosMoneda))
                            {
                                GameObject Ninero = Instantiate(Moneda) as GameObject; //Instacia hierba que si se puede 
                                Ninero.transform.position = new Vector3(PosMoneda * 40, 25, display);
                                posicionada = true;
                            }
                        }
                    }
                    
                   
                    GameObject HierbaIns = Instantiate(Hierba) as GameObject; //Instacia hierba que si se puede 
                    HierbaIns.transform.position = intPos;
                    intPosArbolNoPisar1 = new Vector3(-200, 25, display);
                    intPosArbolNoPisar2 = new Vector3(200, 25, display);
                    //Agregamos arboles a la hierba que no se pisa.
                    ArbolInst = Instantiate(Arboles[tipoArbol]) as GameObject;
                    ArbolInst.transform.position = intPosArbolNoPisar1; //Posiciono primer Arbol.
                    ArbolInst = Instantiate(Arboles[tipoArbol]) as GameObject;
                    ArbolInst.transform.position = intPosArbolNoPisar2; //Posiciono segundo Arbol.
                    display += 40; //El display le sumamos 40


                }
            }
            else if (tipoVia == 2) //pintamos carrertera
            {
                numVias = Random.Range(1, 4);
                if(numVias == 1  && !carretera)// nos evita poner una carretera si hay otra porque las lineas no coinciden.
                {
                    carretera = true;
                    intPos = new Vector3(0, 0.2f, display);
                    display += 40;
                    GameObject CarreteraIns;
                    tipoxDif = Random.Range(difmin,difmax);
                    if(tipoxDif == 0)
                    {
                        if(Random.Range(0,1) == 1)
                        {
                            CarreteraIns  = Instantiate(CarreteraF2) as GameObject;
                        }
                        else
                        {
                            CarreteraIns = Instantiate(Carreteras[tipoxDif]) as GameObject;
                        }
                    }else
                    {
                        CarreteraIns = Instantiate(Carreteras[tipoxDif]) as GameObject;
                    }
                  CarreteraIns.transform.position = intPos;
                } else if(numVias == 2 && !carretera)
                {
                    carretera = true;
                    intPos = new Vector3(0, 0.2f, display+20);
                    display += 80;
                    GameObject CarreteraIns;
                    tipoxDif = Random.Range(difmin, difmax);
                    if (tipoxDif ==1)
                    {
                        if (Random.Range(0, 1) == 1)
                        {
                            CarreteraIns = Instantiate(CarreteraDM2) as GameObject;
                        }
                        else
                        {
                            CarreteraIns = Instantiate(CDobles[tipoxDif]) as GameObject;
                        }
                    } else if (tipoxDif == 2)
                    {
                        if (Random.Range(0, 1) == 1)
                        {
                            CarreteraIns = Instantiate(CarreteraDD2) as GameObject;
                        }
                        else
                        {
                            CarreteraIns = Instantiate(CDobles[tipoxDif]) as GameObject;
                        }
                    }
                    else
                    {
                        CarreteraIns = Instantiate(CDobles[tipoxDif]) as GameObject;
                    }
                    CarreteraIns.transform.position = intPos;
                }
                else if (numVias == 3 && !carretera)
                {
                    carretera = true;
                    intPos = new Vector3(0, 0.2f, display + 40);
                    display += 120;
                    GameObject CarreteraIns;
                    tipoxDif = Random.Range(difmin, difmax);
                    if (tipoxDif == 1)
                    {
                        if (Random.Range(0, 1) == 1)
                        {
                            CarreteraIns = Instantiate(CarreteraTM2) as GameObject;
                        }
                        else
                        {
                            CarreteraIns = Instantiate(CTriples[tipoxDif]) as GameObject;
                        }
                    }else
                    {
                        CarreteraIns = Instantiate(CTriples[tipoxDif]) as GameObject;
                    }
                    CarreteraIns.transform.position = intPos;
                }
            }
            else if (tipoVia == 3)
            {
                carretera = false;
                numVias = Random.Range(1, 3);
                
                for (int i = 0; i < numVias; ++i)  {
                    intPos = new Vector3(0, 0, display);
                    int tipoPlanta = Random.Range(1, 6);
                    List<int> posicionesZ = new List<int>();
                    if (tipoPlanta == 4 && !hayplantas)
                    {
                        hayplantas = true;
                        int numPlantas = Random.Range(3, 6);
                        int posPlantas;
                        GameObject PlantaIns;
                        for (int j = 0; j < numPlantas; ++j) // Pone las plantas spbre el agua
                        {
                            posPlantas = Random.Range(-3, 4); // Se calcula la posicion de las plamtas
                            if (!posicionesZ.Contains(posPlantas))
                            {
                                posicionesZ.Add(posPlantas);
                                intPosArbol = new Vector3(posPlantas * 40, 20, display);
                                tipoArbol = Random.Range(0, 6);
                                PlantaIns = Instantiate(planta) as GameObject;
                                PlantaIns.transform.position = intPosArbol;
                            }
                        }//Plantas
                        GameObject AguaIns = Instantiate(RioSeco) as GameObject;
                        AguaIns.transform.position = intPos;
                       
                        
                    }
                    else {
                        hayplantas = false;
                        tipoxDif = Random.Range(difmin, difmax);
                        int Inverso = Random.Range(0, 2);
                        GameObject AguaIns = Instantiate(Rios[tipoxDif]) as GameObject;
                        AguaIns.transform.position = intPos;
                        if (Inverso == 1)
                        {
                            Component[] Childrens = AguaIns.GetComponentsInChildren(typeof(MovimientoTronco));

                            for (int j = 0; j < Childrens.Length; ++j)
                            {
                                Childrens[j].GetComponent<MovimientoTronco>().setInverso();
                            }
                        }
                    }
                    display += 40;
                }
            }
            else if(tipoVia == 4)
            {
                if(Random.Range(1,4) == 3)
                {
                    intPos = new Vector3(0, 0, display);

                    GameObject carrilTren = Instantiate(Tren) as GameObject;
                    carrilTren.transform.position = intPos;
                    display += 40;
                }
                
            }

        }
            
	}

    public void subirnvl()
    {
        if (difmax < 3) ++difmax;
        else if (difmin < 1) ++difmin; 
    }
}
