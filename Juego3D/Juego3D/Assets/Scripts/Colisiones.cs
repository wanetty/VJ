using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Colisiones : MonoBehaviour {
    void OnCollisionEnter(Collision col)
    {
        GameObject Objeto = GameObject.Find("gallina");

        if (col.gameObject.tag == "Arbol")
        {
            Debug.Log("ParoMovimiento");
            Objeto.GetComponent<Movimiento_player>().haycolision();

        }
        
    }
    void OnCollisionExit(Collision col)
    {
        GameObject Objeto = GameObject.Find("gallina");
        if (col.gameObject.tag == "Arbol")
        {
            Debug.Log("Renuevo movimiento");
            Objeto.GetComponent<Movimiento_player>().notcolision();

        }
    }
}
