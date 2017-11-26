using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SeguimientoCamara : MonoBehaviour {

    public GameObject Jugador;
    Vector3 Posicion;
	// Update is called once per frame
	void Update () {
        Posicion = Vector3.Lerp(gameObject.transform.position, Jugador.transform.position, Time.deltaTime);
        gameObject.transform.position = new Vector3(Posicion.x, 1, Posicion.z);
	}
}
