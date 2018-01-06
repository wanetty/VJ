using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class Colisiones : MonoBehaviour {
    bool tronco = false;
    private Animation anim;
    public AudioClip caeagua;
    public AudioClip hojas;
    public AudioClip crujidoTronco;
    public GameObject Salpicar;
    AudioSource reproductor;
    bool perdido = false;


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
                reproductor.PlayOneShot(hojas, 0.5F);
                Player.GetComponent<Movimiento_player>().haycolision();
            }
            if (col.gameObject.tag == "Agua")
            {
                if (!tronco)
                {
                    reproductor.PlayOneShot(caeagua, 0.5F);
                    Debug.Log("Caigo Agua");
                    Salpicar.transform.position = new Vector3(Player.transform.position.x, 18, Player.transform.position.z);
                    GameObject Salpicadura = Instantiate(Salpicar) as GameObject;
                    Salpicadura.GetComponent<ParticleSystem>().Play();
                    Player.GetComponent<Movimiento_player>().perder();
                    perdido = true;
                    anim.Stop("salto");
                    anim.Play("caerse");
                    
                    
                    

                }
            }
            if (col.gameObject.tag == "carretera")
            {
            }
            if (col.gameObject.tag == "Vehiculo")
            {
                Debug.Log("choco camion");
                anim.Stop("salto");
                anim.Play("estampa");
                float speed = col.gameObject.GetComponentInParent<MovimientoCoche>().getSpeed();
                Player.GetComponent<Movimiento_player>().ArrastraTronco(speed);
                Player.GetComponent<Movimiento_player>().perder();
               perdido = true;
            }
            if (col.gameObject.tag == "Tronco")
            {
                tronco = true;
                col.gameObject.GetComponent<Animation>().Play("apoyarse");
                reproductor.PlayOneShot(crujidoTronco, 0.7F);
                anim.Play("apoyarTronco");
                float speed = col.gameObject.GetComponentInParent<MovimientoTronco>().getSpeed();
                Player.GetComponent<Movimiento_player>().ArrastraTronco(speed);
                Debug.Log(speed.ToString());

            }
            if(col.gameObject.tag == "cesped")
            {
            
                Player.GetComponent<Movimiento_player>().CorregirPos();
            }

        }
    }

    void OnCollisionStay(Collision col)
    {
        //tronco = true;
        if (!perdido)
        {
            reproductor = gameObject.GetComponent<AudioSource>();
            GameObject Player = GameObject.Find("gallina");
            anim = this.GetComponent<Animation>();
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
            if (col.gameObject.tag == "Vehiculo")
            {
                float speed = col.gameObject.GetComponentInParent<MovimientoTronco>().getSpeed();
                Player.GetComponent<Movimiento_player>().ArrastraTronco(speed);
                
            }

        }
    }
    void OnCollisionExit(Collision col)
    {
        if (!perdido)
        {
            GameObject Player = GameObject.Find("gallina");
            if (col.gameObject.tag == "Arbol") Player.GetComponent<Movimiento_player>().notcolision();
            if (col.gameObject.tag == "Tronco") { 
            
                Player.GetComponent<Movimiento_player>().ArrastraTronco(0);
                tronco = false;
            }
            if (col.gameObject.tag == "Agua")
            {
               
            }

        }

    }
}
