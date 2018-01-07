﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class Colisiones : MonoBehaviour {
    bool tronco = false;
    private Animation anim;
    public AudioClip caeagua;
    public AudioClip hojas;
    public AudioClip coins;
    public AudioClip crujidoTronco;
    public GameObject Salpicar;
    public GameObject Plumas;
    public GameObject Hojas;
    AudioSource reproductor;
    bool perdido, estampado= false;
    private bool avanza;

    void Update()
    {
        if (Input.GetButtonUp("arriba")) avanza = true;
        else if (Input.GetButtonUp("abajo")) avanza = false;


    }

    void OnCollisionEnter(Collision col)
    {

        if (!perdido)
        {
            reproductor = gameObject.GetComponent<AudioSource>();
            GameObject Player = GameObject.Find("gallina");
            anim = this.GetComponent<Animation>();

            // tronco = true;//Esto sobra, es para poder pasar sobre el agua sin troncos...
            if (col.gameObject.tag == "Arbol")
            {
                Hojas.transform.position = new Vector3(col.transform.position.x, 50, col.transform.position.z);
                GameObject HojasVolando = Instantiate(Hojas) as GameObject;
                reproductor.PlayOneShot(hojas, 0.5F);
                Player.GetComponent<Movimiento_player>().haycolision();
            }
            else if (col.gameObject.tag == "Moneda")
            {
                reproductor.PlayOneShot(coins, 0.5f);
                Player.GetComponent<Movimiento_player>().MonedaEncontrada();
                Destroy(col.gameObject);
            }
            else if (col.gameObject.tag == "Roca")
            {

                Player.GetComponent<Movimiento_player>().haycolision();
            }
            else if (col.gameObject.tag == "Agua")
            {
                if (!tronco)
                {
                    reproductor.PlayOneShot(caeagua, 0.5F);
                    Salpicar.transform.position = new Vector3(Player.transform.position.x, 18, Player.transform.position.z);
                    GameObject Salpicadura = Instantiate(Salpicar) as GameObject;
                    Salpicadura.GetComponent<ParticleSystem>().Play();
                    Player.GetComponent<Movimiento_player>().sethundido();
                    perdido = true;
                    anim.Stop("salto");
                    anim.Play("caerse");




                }
            }
            else if (col.gameObject.tag == "carretera")
            {
            }
            else if (col.gameObject.tag == "Vehiculo")
            {
                
                anim.Stop("salto");

                if (Player.transform.position.z == col.transform.position.z)
                {
                    Plumas.transform.position = new Vector3(Player.transform.position.x, 18, Player.transform.position.z);
                    GameObject PlumasVolando = Instantiate(Plumas) as GameObject;
                    anim.Play("chafar");
                    Player.GetComponent<Movimiento_player>().setchafado();

                }
                else
                {
                    Component[] Componentes = col.gameObject.GetComponentsInParent(typeof(Cocheinverso));

                    float speed;
                    if (Componentes.Length == 0)
                    {
                        speed = col.gameObject.GetComponentInParent<MovimientoCoche>().getSpeed();
                    }
                    else
                    {
                        speed = col.gameObject.GetComponentInParent<Cocheinverso>().getSpeed();
                    }

                    anim.Play("estampa");
                    Plumas.transform.position = new Vector3(Player.transform.position.x, 18, Player.transform.position.z);
                    GameObject PlumasVolando = Instantiate(Plumas) as GameObject;

                    estampado = true;
                    Player.GetComponent<Movimiento_player>().setestampado(avanza);

                    Player.GetComponent<Movimiento_player>().ArrastraTronco(speed);
                }

                perdido = true;
            }
            else if (col.gameObject.tag == "Tronco")
            {
                tronco = true;
                col.gameObject.GetComponent<Animation>().Play("apoyarse");
                reproductor.PlayOneShot(crujidoTronco, 0.7F);
                anim.Play("apoyarTronco");
                float speed = col.gameObject.GetComponentInParent<MovimientoTronco>().getSpeed();
                Player.GetComponent<Movimiento_player>().ArrastraTronco(speed);


            }
            else if (col.gameObject.tag == "Planta")
            {
                tronco = true;
                col.gameObject.GetComponent<Animation>().Play("apoyarse");
                anim.Play("apoyarTronco");


            }
            else if (col.gameObject.tag == "cesped")
            {

                Player.GetComponent<Movimiento_player>().CorregirPos();
            }

        }
    }

    void OnCollisionStay(Collision col)
    {
        //tronco = true;
        reproductor = gameObject.GetComponent<AudioSource>();
        GameObject Player = GameObject.Find("gallina");
        anim = this.GetComponent<Animation>();
        if (!perdido)
        {
            /*if (col.gameObject.tag == "Agua")
            {
                if (!tronco)
                {
                    reproductor.PlayOneShot(caeagua, 0.5F);
                    Debug.Log("Caigo Agua");
                    anim.Stop("salto");
                    anim.Play("caerse");
                    Player.GetComponent<Movimiento_player>().perder();
                    perdido = true;
                }
            }*/
            if (col.gameObject.tag == "Tronco")
            {
                tronco = true;
                float speed = col.gameObject.GetComponentInParent<MovimientoTronco>().getSpeed();
                Player.GetComponent<Movimiento_player>().ArrastraTronco(speed);
            }
            if (col.gameObject.tag == "Planta")
            {
                tronco = true;
            }
        }
        else{
            if (col.gameObject.tag == "Vehiculo")
            {
                if (estampado)
                {
                    Component[] Componentes = col.gameObject.GetComponentsInParent(typeof(Cocheinverso));
                    
                    float speed;
                    if (Componentes.Length  == 0)
                    {
                        speed = col.gameObject.GetComponentInParent<MovimientoCoche>().getSpeed();
                    }
                    else
                    {
                        speed = col.gameObject.GetComponentInParent<Cocheinverso>().getSpeed();
                    }
                    Player.GetComponent<Movimiento_player>().ArrastraTronco(speed);
                }
            }
        }
    }
    void OnCollisionExit(Collision col)
    {
        if (!perdido)
        {
            GameObject Player = GameObject.Find("gallina");
            if (col.gameObject.tag == "Arbol"  || col.gameObject.tag == "Roca") Player.GetComponent<Movimiento_player>().notcolision();
            if (col.gameObject.tag == "Tronco") { 
            
                Player.GetComponent<Movimiento_player>().ArrastraTronco(0);
                tronco = false;
                    Debug.Log("SalgoTrocno");
            }
           if(col.gameObject.tag == "Planta") {

                Debug.Log("SalgoPlanta");
                tronco = false;
            }
            

        }

    }
}
