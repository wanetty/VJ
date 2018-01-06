using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControladorJuego : MonoBehaviour {

    private float oldpos;
    private bool lost;
    private float time;
    private bool atrapado;
    public GameObject aguila;
    private GameObject aguilucha;
    public AudioClip ataca;
    AudioSource reproductor;


    // Use this for initialization
    void Start () {
        lost = false;
        oldpos = 0;
        time = 0;
        atrapado = false;
        reproductor = gameObject.GetComponent<AudioSource>();
    }
	
	// Update is called once per frame
	void Update () {

        GameObject jugador = GameObject.Find("gallina");
        float pos = jugador.transform.position.z;
        time += Time.deltaTime;
        if (pos <= oldpos && time > 7 && !lost)
        {
            lost = true;
           
            aguilucha = Instantiate(aguila) as GameObject;
            aguilucha.GetComponent<aguila>().setParam(-400, pos + 400);
            aguilucha.transform.position = new Vector3(jugador.transform.position.x, jugador.transform.position.y+60, pos + 400);
            reproductor.PlayOneShot(ataca, 1F);
        }
        else if (pos == oldpos && !lost)
        {
            time += Time.deltaTime;
        }

        
        else
        {
            oldpos = pos;
            time = 0;
        }
        if (lost && !atrapado)
        {
            
            if (aguilucha.transform.position.z <= jugador.transform.position.z)
            {
                
                jugador.GetComponent<Movimiento_player>().Atrapado();
               
                atrapado = true;
            }
        }
    }
}
