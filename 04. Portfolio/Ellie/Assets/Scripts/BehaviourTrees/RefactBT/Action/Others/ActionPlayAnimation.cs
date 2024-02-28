using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionPlayAnimation : MonsterNode
    {
        Animator animator;
        private AnimationType animation;
        private bool waitToEnd;
        private float animationLength;
        private float accumTime;

        public ActionPlayAnimation(AnimationType animation, bool waitToEnd = false)
        {
            if(animator==null)
                animator = tree.GetComponentData<Animator>(MonsterComponentData.ANIMATOR);
            if (animator == null)
                DebugNull(transform, MonsterComponentData.ANIMATOR);

            this.animation = animation;
            this.waitToEnd = waitToEnd;
        }
        protected override void OnStart()
        {
            animator.SetTrigger(animation.ToString());

            if (waitToEnd)
            {
                accumTime = 0;
                AnimatorClipInfo[] clipInfo = animator.GetCurrentAnimatorClipInfo(0);
                animationLength = clipInfo[0].clip.length;
            }
        }
        public override NodeState Evaluate()
        {            
            if(waitToEnd)
            {
                if (accumTime <= animationLength)
                {
                    accumTime += Time.deltaTime;
                    return NodeState.RUNNING;
                }
                else return NodeState.SUCCESS;
            }

            return NodeState.SUCCESS;
        }
    }
}