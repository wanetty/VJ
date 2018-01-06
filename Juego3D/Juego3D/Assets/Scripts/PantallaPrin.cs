using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PantallaPrin : MonoBehaviour {
    public Button Inicio;
    public Scene NivelPrincipal;
    // Use this for initialization
    void Start () {
        Button IniciarJuego = Inicio.GetComponent<Button>();
        IniciarJuego.onClick.AddListener(TaskOnClick);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void TaskOnClick()
    {
        
       SceneManager.LoadScene("EscenaEduard");
    }
}
