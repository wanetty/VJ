﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PointsText : MonoBehaviour {

    GameObject player;
    Text score;
	void Start () {
        player = GameObject.Find("gallina");
    }
	
	// Update is called once per frame
	void Update () {
        int puntos = player.GetComponent<Movimiento_player>().getPuntos();
        this.gameObject.GetComponent<Text>().text = "Score: " + puntos.ToString();
    }
}