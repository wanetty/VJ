using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class Colisiones : MonoBehaviour {
    bool tronco = false;
    private Animation anim;
    public AudioClip caeagua;
    public AudioClip hojas;
    AudioSource reproductor;

    void OnCollisionEnter(Collision col)
    {
        reproductor = gameObject.GetComponent<AudioSource>();
        GameObject Player = GameObject.Find("gallina");
        anim = this.GetComponent<Animation>();
        tronco = true;//Esto sobra, es para poder pasar sobre el agua sin troncos...
        if (col.gameObject.tag == "Arbol")
        {
            reproductor.PlayOneShot(hojas,0.5F);
            Player.GetComponent<Movimiento_player>().haycolision();
        }
        if (col.gameObject.tag == "Agua")
        {
            if (!tronco)
            {
                reproductor.PlayOneShot(caeagua, 0.5F);
                Debug.Log("Caigo Agua");
                anim.Stop("salto");
                anim.Play("caerse");
                Player.GetComponent<Movimiento_player>().perder();

            }
        }
        if (col.gameObject.tag == "camion")
        {
            Debug.Log("choco camion");
            anim.Stop("salto");
            anim.Play("chafado");
            Player.GetComponent<Movimiento_player>().perder();
        }
        
    }
    void OnCollisionExit(Collision col)
    {
        GameObject Player = GameObject.Find("gallina");
        if (col.gameObject.tag == "Arbol") Player.GetComponent<Movimiento_player>().notcolision();
    }
}
