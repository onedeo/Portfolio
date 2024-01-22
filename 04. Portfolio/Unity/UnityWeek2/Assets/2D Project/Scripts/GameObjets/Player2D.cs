using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
/*
 * Sorting Layer은 어느 sprite를 먼저, 혹은 위에 렌더링 할것인지 우선순위 주는 것 (0번부터 그린다)
 * Order in Layer은 같은 SortingLayer이라도 우선순위를 줄 수 있다.
 */

enum STATE { PLAY, PAUSE, DAMAGED}
public class Player2D : MonoBehaviour
{
    STATE playerState=STATE.PLAY;

    public PlayerMissile2D missile;

    private Rigidbody2D rigidBody;
    private Collider2D playerCollider;
    private float maxSpeed = 1000;
    new SpriteRenderer renderer;

    private float fFireAccum = 0.5f;

    public Image imageHPbar;

    private bool bPlay;

    private void Start()
    {
        rigidBody = gameObject.GetComponent<Rigidbody2D>();
        renderer = gameObject.GetComponent<SpriteRenderer>();
        imageHPbar = GetComponentInChildren<Image>();
        playerCollider = gameObject.GetComponent<Collider2D>();

        EventBus2D.Subscribe(EventBus2DType.ADD_SCORE, AddCoinAnim);
        EventBus2D.Subscribe(EventBus2DType.PLAYER_HIT, PlayerHit);
        EventBus2D.Subscribe(EventBus2DType.PLAY, StartGame);
        EventBus2D.Subscribe(EventBus2DType.OVER, StopGame);
    }
    private void Update()
    {
        if (!bPlay) return;
        float x = Input.GetAxis("Horizontal");
        float y = Input.GetAxis("Vertical");

        //Flip_2D(x);
        Move_2(x, y);

        fFireAccum += Time.deltaTime;
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (fFireAccum > 0.3)
            {
                Instantiate(missile, transform.position, transform.rotation);
                fFireAccum = 0;
            }
        }
    }
    void Move_1(float x, float y)
    {
        rigidBody.AddForce(new Vector2(x * maxSpeed * Time.deltaTime, y * maxSpeed * Time.deltaTime));
    }
    void Move_2(float x, float y)
    {
        Vector3 position = transform.position;
        position = new Vector3(position.x + x * maxSpeed * Time.deltaTime, position.y + y * maxSpeed * Time.deltaTime,transform.position.z);
        rigidBody.MovePosition(position);
    }
    
    void Flip_2D(float x)
    {
        if(Mathf.Abs(x)>0)
        {
            if(x>=0)
            {
                renderer.flipX = false;
            }
           else
            {
                renderer.flipX = true;
            }
        }
    }

    void PlayerHit()
    {

        imageHPbar.fillAmount = DataManager2D.GetInstance().GetPlayerHP() / (float)5; 

        playerCollider.enabled = false;
        StartCoroutine("PlayerInvincible");
    }
    IEnumerator PlayerInvincible()
    {
        Color noAlpha = renderer.color;
        for(int i=0; i<3;i++)
        {
            noAlpha.a = 0;
            renderer.color = noAlpha;
            yield return new WaitForSeconds(0.2f);
            noAlpha.a = 1;
            renderer.color = noAlpha;
            yield return new WaitForSeconds(0.2f);
        }
        playerCollider.enabled = true;
    }

    private void AddCoinAnim()
    {
        Debug.Log("Player Add Coin Activated");
    }

    private void StartGame()
    {
        bPlay = true;
    }
    private void StopGame()
    {
        bPlay = false;
    }

}
