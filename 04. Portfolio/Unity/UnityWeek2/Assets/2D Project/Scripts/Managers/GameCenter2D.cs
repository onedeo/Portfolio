using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameCenter2D : Singleton<GameCenter2D>
{
    private void Start()
    {
        EventBus2D.Publish(EventBus2DType.START);
    }
   
    public void GameOver()
    {
        
    }

}
