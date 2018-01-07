using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class aguila : MonoBehaviour {

    public float speed;
    public float EndPosition;
    public float StartPosition;



    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        Vector3 position = this.transform.position;

        
        position.z += speed * Time.deltaTime;
        this.transform.position = position;

    }

    public void setParam(float speed, float starPosition)
    {
        this.speed = speed;
        this.StartPosition = starPosition;
    }
}
