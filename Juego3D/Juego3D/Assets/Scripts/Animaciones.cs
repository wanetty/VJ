﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Animaciones: MonoBehaviour {

	
	// Update is called once per frame
	void Update () {
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