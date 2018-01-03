using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class tren : MonoBehaviour {

    public float speed;
    public float EndPosition;
    public float StartPosition;
     public float time;
   public bool pasando;
    public float time2;
    GameObject sem;
    GameObject luzizquierda;
    GameObject luzderecha;
    Light luziz;
    Light luzde;

    // Use this for initialization
    void Start()
    {
        time = 0;
        pasando = false;
         sem = gameObject.transform.Find("semaforo").gameObject;
        luzizquierda = sem.transform.Find("luziz").gameObject;
        luzderecha = sem.transform.Find("luzde").gameObject;
        luziz = luzizquierda.GetComponent<Light>();
        luzde = luzderecha.GetComponent<Light>();
        time2 = 0;
        
    }

    // Update is called once per frame
    void Update()
    {
        
        pasando = gameObject.transform.Find("vagones").gameObject.GetComponent<vagones>().getPasando();
        if (pasando)
            time2 += Time.deltaTime;
        {
            if((int)(time2 % 2) == 0)
            {
                luziz.intensity = 0;
                luzde.intensity = 50;
                
            }
            else if ((int)(time2 % 2) == 1)
            {
                luziz.intensity = 50;
                luzde.intensity = 0;
                

            }

        }


        if (!pasando)
        {
            time += Time.deltaTime;
            luziz.intensity = 0;
            luzde.intensity = 0;
            if (time >= 5)
            {
                pasando = true;
                luziz.intensity = 50;
                luzde.intensity = 0;
                gameObject.transform.Find("vagones").gameObject.GetComponent<vagones>().setPasando();
                time = 0;
                time2 = 0;
               
            }

        }
          
       
    }
}
