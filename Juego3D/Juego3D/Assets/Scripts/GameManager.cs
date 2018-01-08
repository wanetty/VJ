using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour {
    Canvas perder;
    GameObject jugador;
    bool lostgame;
    
    // Use this for initialization
    void Start () {
        perder = GameObject.Find("Canvas_perder").GetComponent<Canvas>();
        jugador = GameObject.Find("gallina");
        lostgame = false;

    }
	
	// Update is called once per frame
	void Update () {
        
        if (jugador.GetComponent<Movimiento_player>().Notaguila() && !lostgame)
        {
            
            perder.enabled = !perder.enabled;
            lostgame = true;
        }
        else if (jugador.GetComponent<Movimiento_player>().getAtrapado() && !lostgame)
        {

            perder.enabled = !perder.enabled;
            lostgame = true;
        }
    }
}
