using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

[RequireComponent(typeof(Rigidbody), typeof(CapsuleCollider))]

public class PlayerMovement : MonoBehaviour
{
    enum PlayerState
    {
        Idle = 1,
        Move,
        Attack,
        Damage,
        Die,
    };

    [SerializeField] private FixedJoystick joystick;
    [SerializeField] private Button attackButton;

    private Rigidbody rigidbody;
    private Animator animator;

    [SerializeField] private float moveSpeed;

    private void Awake()
    {
        if (rigidbody == null)
            rigidbody = GetComponent<Rigidbody>();
        if (joystick == null)
            Debug.Log("Player And Joystick Is Not Connectec");
        if (animator == null)
            animator = GetComponent<Animator>();
    }

    private void FixedUpdate()
    {
        rigidbody.velocity = new Vector3(joystick.Horizontal * moveSpeed, rigidbody.velocity.y, joystick.Vertical * moveSpeed);

        

        if (joystick.Horizontal != 0 || joystick.Vertical != 0)
        {
            transform.rotation = Quaternion.LookRotation(rigidbody.velocity);
            PlayAnimation(PlayerState.Move);
        }
        else
        {
            PlayAnimation(PlayerState.Idle);
        }
    }

    private void PlayAnimation(PlayerState _animation)
    {
        animator.SetInteger("animation", (int)_animation);
    }

    private void OnActionAttack()
    {
        PlayAnimation(PlayerState.Attack);
    }


}
