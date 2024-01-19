using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class AudioPlay : Node
    {
        private MonsterAudioType audioType;
        private bool isLoop;
        private bool isInteruptable;
        private Transform transform;
        private AudioSource audioSource;
        private MonsterAudioController audioController;
        AudioPlay(Transform transform, MonsterAudioType audioType, bool isInteruptable = true, bool isLoop = true) : base()
        {
            this.audioType = audioType;
            this.isLoop = isLoop;
            this.isInteruptable = isInteruptable;
            this.transform = transform;
        }

        protected override void OnStart()
        {
            if (audioSource == null)
                audioSource = transform.GetComponent<AudioSource>();
            if (audioController == null)
                audioController = transform.GetComponent<MonsterAudioController>();
        }
        public override NodeState Evaluate()
        {
            if (audioSource == null)
            {
                Debug.Log(transform.name + "Has No Audio Source");
                return NodeState.FAILURE;
            }
            if(audioController==null)
            {
                Debug.Log(transform.name + "Has No Audio Controller");
                return NodeState.FAILURE;
            }

            if (isLoop)
                audioSource.loop = true;
            else audioSource.loop = false;

            if (!isInteruptable)
            {
                if (audioSource.isPlaying)
                    return NodeState.SUCCESS;
            }

            AudioClip clip = audioController.GetAudio(audioType);
            if(clip==null)
            {
                Debug.Log(transform.name + "Try To Play Audio Does Not Have: " + audioType.ToString());
                return NodeState.FAILURE;
            }
            audioSource.clip = clip;
            audioSource.Play();

            return NodeState.SUCCESS;
        }

    }
}