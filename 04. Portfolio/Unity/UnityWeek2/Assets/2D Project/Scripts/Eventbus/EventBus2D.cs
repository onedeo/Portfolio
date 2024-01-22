using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.Events;

public class EventBus2D
{
    private static readonly IDictionary<EventBus2DType, UnityEvent>
        Events = new Dictionary<EventBus2DType, UnityEvent>();

    public static void Subscribe(EventBus2DType _type, UnityAction _listener)
    {
        UnityEvent thisEvent;

        if (Events.TryGetValue(_type, out thisEvent))
        {
            thisEvent.AddListener(_listener);
        }
        else
        {
            thisEvent = new UnityEvent();
            thisEvent.AddListener(_listener);
            Events.Add(_type, thisEvent);
        }
    }

    public static void UnSubscribe(EventBus2DType _type, UnityAction _listener)
    {
        UnityEvent thisEvent;
        if(Events.TryGetValue(_type, out thisEvent))
        {
            thisEvent.RemoveListener(_listener);
        }
    }
    public static void Publish(EventBus2DType _type)
    {
        UnityEvent thisEvent;
        if(Events.TryGetValue(_type, out thisEvent))
        {
            thisEvent.Invoke();
        }
    }
}
