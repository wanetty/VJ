using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movimiento_player : MonoBehaviour
{
    
    public float saltovelociad = 5;
    public float speedescala = 3;
    public Transform hijo;
    public float MovimientoEscala = 0.01f;
    public AnimationCurve ac;
    public Animation animacion;

    float currentLerpTime;
    float currentScaleTime;
    float perc = 1;
    float scalePerc;
    bool firstinput;
    bool colision;

    Vector3 Posini;
    Vector3 startPos;
    Vector3 endPos;

    Vector3 startScale;
    Vector3 endScale;


    bool primero;

    // Use this for initialization
    void Start()
    {
        animacion = gameObject.transform.Find("default").GetComponent<Animation>();
        hijo = gameObject.transform.Find("default");
        colision = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetButtonDown("arriba") || Input.GetButtonDown("abajo") || Input.GetButtonDown("der") || Input.GetButtonDown("izq"))
        {
            
            currentScaleTime = 0;
            
        }
        if (Input.GetButton("arriba") || Input.GetButton("abajo") || Input.GetButton("der") || Input.GetButton("izq") )
        {
            startScale = gameObject.transform.localScale;
            
            if (transform.localScale.y - MovimientoEscala > 0.9f)
            {
                endScale = new Vector3(transform.localScale.x + MovimientoEscala, transform.localScale.y - MovimientoEscala, transform.localScale.z);
            }
            firstinput = true;

        }
        if (Input.GetButtonUp("arriba") || Input.GetButtonUp("abajo") || Input.GetButtonUp("der") || Input.GetButtonUp("izq"))
        {
            if (perc >= 1)
            {
                Posini = gameObject.transform.position;
                animacion.Play("salto");
                currentLerpTime = 0;
                currentScaleTime = 0;
                perc = 0;
                startPos = gameObject.transform.position;
                startScale = gameObject.transform.localScale;
                endScale = new Vector3(1f,1f, 1f);
            }

        }

        startPos = gameObject.transform.position;
        if (Input.GetButtonUp("izq") && gameObject.transform.position == endPos && gameObject.transform.position.x < 160 && !colision)
        {
            endPos = new Vector3(transform.position.x + 40, transform.position.y, transform.position.z);
        }
        if (Input.GetButtonUp("der") && gameObject.transform.position == endPos && gameObject.transform.position.x > -160 && !colision)
        {
            endPos = new Vector3(transform.position.x - 40, transform.position.y, transform.position.z );
        }
        if (Input.GetButtonUp("arriba") && gameObject.transform.position == endPos && !colision)
        {
            endPos = new Vector3(transform.position.x, transform.position.y, transform.position.z + 40);
        }
        if (Input.GetButtonUp("abajo") && gameObject.transform.position == endPos && !colision)
        {
            endPos = new Vector3(transform.position.x, transform.position.y, transform.position.z - 40);
        }

        if (firstinput)
        {
            currentLerpTime += Time.deltaTime * saltovelociad;
            perc = currentLerpTime;
            if (colision) endPos = Posini; 
            gameObject.transform.position = Vector3.Lerp(startPos, endPos, ac.Evaluate(perc));
            currentScaleTime += Time.deltaTime * speedescala;
            scalePerc = currentScaleTime;
            gameObject.transform.localScale = Vector3.Lerp(startScale, endScale, ac.Evaluate(scalePerc));
        }
    }
    public void haycolision()
    {
        colision = true;    
    }

    public void notcolision()
    {
        colision = false;
    }

    

}

