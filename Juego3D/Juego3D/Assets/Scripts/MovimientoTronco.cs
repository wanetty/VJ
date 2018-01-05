using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovimientoTronco : MonoBehaviour {

    public float speed;
    public float EndPosition;
    public float StartPosition;
    private float speedaux;
    private float speedOut;
    private float speedIn;
    public bool inverso;


    // Use this for initialization
    void Start()
    {
        if (inverso)
        {
            speedOut = 250;
            speedIn = speed * -1;
            speed *= -1;
            StartPosition *=  -1;
            EndPosition *= -1;
            
        }
        else
        {
            speedOut = -250;
            speedIn = speed;
        }
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 position = this.transform.position;
        speedaux = speed * Time.deltaTime;
        float oldPosition = position.x;
        position.x += speedaux;
        this.transform.position = position;
        if (inverso)
        {
            if (position.x > 170)
            {
                speed = speedOut;
            }
            if (oldPosition < position.x)
            {
                if (position.x > EndPosition)
                {
                    speed = speedIn;
                    position.x = StartPosition;
                    this.transform.position = position;

                }
            }
        }
        else
        {
            if (position.x < -170)
            {
                speed = speedOut;
            }
            if (oldPosition > position.x)
            {
                if (position.x < EndPosition)
                {
                    speed = speedIn;
                    position.x = StartPosition;
                    this.transform.position = position;

                }
            }
        }
        
    }
    public float getSpeed()
    {
        return speedaux;
    }
}
