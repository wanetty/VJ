﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovimientoCoche : MonoBehaviour {

    public float speed;
    public float EndPosition;
    public float StartPosition;


	// Use this for initialization
	void Start () {
     
	}
	
	// Update is called once per frame
	void Update () {
        Vector3 position = this.transform.position;

        float oldPosition = position.x;
        position.x += speed * Time.deltaTime;
        this.transform.position = position;
        if (oldPosition > position.x)
        {
            if (position.x < EndPosition)
            {
                Debug.Log("salgo de la carretera vuelvo al inicio");
                position.x = StartPosition;
                this.transform.position = position;
            }
        }
	}
}
