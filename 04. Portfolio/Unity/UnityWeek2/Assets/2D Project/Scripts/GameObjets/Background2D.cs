using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Background2D : MonoBehaviour
{
    private SpriteRenderer renderer;
    public Background2D back1;

    private float color;
    private void Start()
    {
        renderer = gameObject.GetComponent<SpriteRenderer>();
        StartCoroutine("ChangeColor");
    }

    private void Update()
    {
        transform.Translate(Vector3.right * -150 * Time.deltaTime);


    }


    private void OnTriggerExit2D(Collider2D collision)
    {
        if(collision.CompareTag("MissileCut"))
        {
            Vector3 newpos = transform.position;
            newpos.x += 1040;
            back1.transform.position = newpos;
        }
    }

    private IEnumerator ChangeColor()
    {
        Color newColor = renderer.color;
        int count = 0;
        bool down = true;
        while (true)
        {
            if (count == 0)
            {
                if (down)
                {
                    newColor.r -= 0.1f;
                    if (newColor.r == 0)
                        down = false;
                }
                else
                {
                    newColor.r += 0.1f;
                    if (newColor.r == 1)
                        count++;
                }
            }
            if (count == 1)
            {
                if (down)
                {
                    newColor.g -= 0.1f;
                    if (newColor.g == 0)
                        down = false;
                }
                else
                {
                    newColor.g += 0.1f;
                    if (newColor.g == 1)
                        count++;
                }
            }
            if (count == 2)
            {
                if (down)
                {
                    newColor.b -= 0.1f;
                    if (newColor.b == 0)
                        down = false;
                }
                else
                {
                    newColor.b += 0.1f;
                    if (newColor.b == 1)
                        count=0;
                }
            }

            renderer.color = newColor;
            yield return new WaitForSeconds(1f);
        }
    }
}
