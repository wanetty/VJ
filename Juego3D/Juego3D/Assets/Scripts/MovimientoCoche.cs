using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovimientoCoche : MonoBehaviour {

    public float speed;
    public float EndPosition;
    public float StartPosition;
    private float speedaux;


	// Use this for initialization
	void Start () {
     
	}
	
	// Update is called once per frame
	void Update () {
        Vector3 position = this.transform.position;
        speedaux = speed * Time.deltaTime;
        float oldPosition = position.x;
        position.x += speedaux;
        this.transform.position = position;
        if (oldPosition > position.x)
        {
            if (position.x < EndPosition)
            {
               
                position.x = StartPosition;
                this.transform.position = position;
            }
        }
	}
    public float getSpeed()
    {
        return speedaux;
    }
}
