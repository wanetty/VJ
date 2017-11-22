﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movimiento_player : MonoBehaviour {
    float lerpTime;
    float currentTime;
    float perc = 1;
    Vector3 startPos;
    Vector3 endPos;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetButtonDown("arriba") || Input.GetButtonDown("abajo") || Input.GetButtonDown("der") || Input.GetButtonDown("izq"))
        {
            if(perc == 1)
            {
                lerpTime = 1;
                currentTime = 0;
            }
            startPos = gameObject.transform.position;
            if(Input.GetButtonDown("izq") && gameObject.transform.position == endPos)
            {
                endPos = new Vector3(transform.position.x + 1, transform.position.y, transform.position.z);
            }
            if (Input.GetButtonDown("der") && gameObject.transform.position == endPos)
            {
                endPos = new Vector3(transform.position.x - 1, transform.position.y, transform.position.z);
            }
            if (Input.GetButtonDown("arriba") && gameObject.transform.position == endPos)
            {
                endPos = new Vector3(transform.position.x , transform.position.y, transform.position.z+1);
            }
            if (Input.GetButtonDown("abajo") && gameObject.transform.position == endPos)
            {
                endPos = new Vector3(transform.position.x, transform.position.y, transform.position.z-1);
            }
            currentTime += Time.deltaTime * 5.5f;
            perc = currentTime / lerpTime;
            gameObject.transform.position = Vector3.Lerp(startPos, endPos, perc);

        }
	}
}