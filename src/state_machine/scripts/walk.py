#!/usr/bin/env python

import rospy
import smach
import smach_ros
from std_msgs.msg import Float32
from std_msgs.msg import Int32

c = 42000

d1 = 1.*c/360*30
d2 = 1.*c/360*180
d3 = 1.*c/360*210

class init(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1'])

    def execute(self,userdata):
        return 'outcome1'

class start_leg1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1','outcome2'])
        self.walk=0
        self.subscriber = rospy.Subscriber('/enc0',Int32,self.encCb)
        self.con=0
        self.subscriber = rospy.Subscriber('/time',Int32,self.timeCb)

    def encCb(self,msg):
        self.walk=msg.data

    def timeCb(self,msg):
        self.con=msg.data

    def execute(self,userdata):
        pub0 = rospy.Publisher('motorcon0',Float32,queue_size=10)
        pub0_msg = self.con
        pub0.publish(pub0_msg)

        rospy.sleep(0.2)
        if self.walk < 1.*42000/360*30:
            return 'outcome1'
        else:
            #pub_msg = 0;
            #pub.publish(pub_msg);
            return 'outcome2'


class start_leg2(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1','outcome2'])
        self.walk=0
        self.subscriber = rospy.Subscriber('/enc0',Int32,self.encCb)
        self.con=0
        self.subscriber = rospy.Subscriber('/time',Int32,self.timeCb)

    def encCb(self,msg):
        self.walk=msg.data

    def timeCb(self,msg):
        self.con=msg.data

    def execute(self,userdata):
        pub0 = rospy.Publisher('motorcon0',Float32,queue_size=10)
        pub0_msg = self.con
        pub0.publish(pub0_msg)

        pub2 = rospy.Publisher('motorcon2',Float32,queue_size=10)
        pub2_msg = self.con-d1
        pub2.publish(pub2_msg)
        rospy.sleep(0.2)
        if self.walk < d2:
            return 'outcome1'
        else:
            #pub_msg = 0;
            #pub.publish(pub_msg);
            return 'outcome2'

class start_leg3(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1','outcome2'])
        self.walk=0
        self.subscriber = rospy.Subscriber('/enc0',Int32,self.encCb)
        self.con=0
        self.subscriber = rospy.Subscriber('/time',Int32,self.timeCb)

    def encCb(self,msg):
        self.walk=msg.data

    def timeCb(self,msg):
        self.con=msg.data

    def execute(self,userdata):
        pub0 = rospy.Publisher('motorcon0',Float32,queue_size=10)
        pub0_msg = self.con
        pub0.publish(pub0_msg)

        pub2 = rospy.Publisher('motorcon2',Float32,queue_size=10)
        pub2_msg = self.con-d1
        pub2.publish(pub2_msg)

        pub1 = rospy.Publisher('motorcon1',Float32,queue_size=10)
        pub1_msg = self.con-d2
        pub1.publish(pub1_msg)
        rospy.sleep(0.2)
        if self.walk < d3:
            return 'outcome1'
        else:
            #pub_msg = 0;
            #pub.publish(pub_msg);
            return 'outcome2'

class walk(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1','outcome2'])

        self.con=0
        self.subscriber = rospy.Subscriber('/time',Int32,self.timeCb)

    def timeCb(self,msg):
        self.con=msg.data

    def execute(self,userdata):
        pub0 = rospy.Publisher('motorcon0',Float32,queue_size=10)
        pub0_msg = self.con
        pub0.publish(pub0_msg)

        pub2 = rospy.Publisher('motorcon2',Float32,queue_size=10)
        pub2_msg = self.con-d1
        pub2.publish(pub2_msg)

        pub1 = rospy.Publisher('motorcon1',Float32,queue_size=10)
        pub1_msg = self.con-d2
        pub1.publish(pub1_msg)

        pub3 = rospy.Publisher('motorcon3',Float32,queue_size=10)
        pub3_msg = self.con-d3
        pub3.publish(pub3_msg)
        rospy.sleep(0.2)
        return 'outcome1'

class stop(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1','outcome2'])
        self.counter=0


    def execute(self,userdata):
        pub0 = rospy.Publisher('motor0',Float32,queue_size=10)
        pub1 = rospy.Publisher('motor1',Float32,queue_size=10)
        pub2 = rospy.Publisher('motor2',Float32,queue_size=10)
        pub3 = rospy.Publisher('motor3',Float32,queue_size=10)
        pub_msg = 0
        pub0.publish(pub_msg)
        pub1.publish(pub_msg)
        pub2.publish(pub_msg)
        pub3.publish(pub_msg)
        rospy.sleep(1)
        if self.counter < 10:
            self.counter += 1
            return 'outcome1'
        else:
            return 'outcome2'

class main():
    rospy.init_node('smach_walk')
    sm=smach.StateMachine(
            outcomes=['outcome3'])

    with sm:
        smach.StateMachine.add(
                'init', init(),
                transitions=
                    {'outcome1':'start_leg1'})

        smach.StateMachine.add(
                'start_leg1',start_leg1(),
                transitions=
                    {'outcome1':'start_leg1', 
                     'outcome2':'start_leg2'})

        smach.StateMachine.add(
                'start_leg2',start_leg2(),
                transitions=
                    {'outcome1':'start_leg2',
                     'outcome2':'start_leg3'})

        smach.StateMachine.add(
                'start_leg3',start_leg3(),
                transitions=
                    {'outcome1':'start_leg3',
                     'outcome2':'walk'})

        smach.StateMachine.add(
                'walk',walk(),
                transitions=
                    {'outcome1':'walk',
                     'outcome2':'stop'})

        smach.StateMachine.add(
                'stop',stop(),
                transitions=
                    {'outcome1':'stop',
                     'outcome2':'init'})

        sis = smach_ros.IntrospectionServer('server_name',sm,'/SM_ROOT')
        sis.start()

        outcome=sm.execute()
        rospy.spin()

if __name__ == '__main__':
    main()
