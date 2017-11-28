using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Animaciones: MonoBehaviour {

    Animator animaciones;
    public GameObject Jugador;
	void Start () {
        animaciones = gameObject.GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
        Movimiento_player Mov_player = Jugador.GetComponent<Movimiento_player>();
        if (Mov_player.saltando == true)
        {
            animaciones.SetBool("Saltando", true);
        }
        else
        {
            animaciones.SetBool("Saltando", false);
        }
        if (Input.GetButtonDown("izq"))
        {
            gameObject.transform.rotation = Quaternion.Euler(0, 90, 0);
        }
        if (Input.GetButtonDown("der"))
        {
            gameObject.transform.rotation = Quaternion.Euler(0, -90, 0);
        }
        if (Input.GetButtonDown("arriba"))
        {
            gameObject.transform.rotation = Quaternion.Euler(0, 0, 0);
        }
        if (Input.GetButtonDown("abajo"))
        {
            gameObject.transform.rotation = Quaternion.Euler(0, 180, 0);
        }
    }
}
