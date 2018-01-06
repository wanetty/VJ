﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class vagones : MonoBehaviour {

    public float speed;
    public float EndPosition;
    public float StartPosition;
    private bool pasando;

    // Use this for initialization
    void Start()
    {
        pasando = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (pasando) { 

            Vector3 position = this.transform.position;

            float oldPosition = position.x;
            position.x += speed * Time.deltaTime;
            this.transform.position = position;
            if (oldPosition > position.x)
            {
                if (position.x < EndPosition)
                {
                
                position.x = StartPosition;
                this.transform.position = position;
                pasando = false;
                }
            }
         }
    }

    public void setPasando()
    {
        pasando = true;
    }
    public bool getPasando()
    {
        return pasando;
    }
}