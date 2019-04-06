#!/usr/bin/env python

import rospy
import smach
import smach_ros
from std_msgs.msg import Int16
from std_msgs.msg import Empty
from std_msgs.msg import Bool

count=34
speed=90
delay=0.05

class Init(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.sb=False;
        self.s=rospy.Subscriber('switch0',Bool,self.sCb);
    def sCb(self,msg):
        self.sb=msg.data;
    def execute(self,data):
        rospy.sleep(0.5)
        if self.sb:
            return 'next'
        else:
            return 'id'

class Set(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.r0=rospy.Publisher('/motor0/reset',Empty)
        self.r1=rospy.Publisher('/motor1/reset',Empty)
        self.r2=rospy.Publisher('/motor2/reset',Empty)
        self.r3=rospy.Publisher('/motor3/reset',Empty)
    def execute(self,data):
        self.r0.publish()
        self.r1.publish()
        self.r2.publish()
        self.r3.publish()
        rospy.sleep(0.5)
        return 'next'

class M0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.s=rospy.Subscriber('/motor0/zero',Int16,self.encCb)
        self.p=rospy.Publisher('/motor0/motor',Int16)
        self.off=rospy.Publisher('/motor0/off',Empty)
        self.zero=0

        global speed
        self.speed=speed
        global count
        self.count=count
        global delay
        self.delay=delay

    def encCb(self,msg):
        self.zero=msg.data
    def execute(self,data):
        rospy.sleep(self.delay)
        if self.zero<=self.count:
            self.p.publish(self.speed)
            return 'id'
        else:
            self.off.publish()
            return 'next'

class M2(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.s=rospy.Subscriber('/motor2/zero',Int16,self.encCb)
        self.p=rospy.Publisher('/motor2/motor',Int16)
        self.off=rospy.Publisher('/motor2/off',Empty)
        self.zero=0

        global speed
        self.speed=speed
        global count
        self.count=count
        global delay
        self.delay=delay

    def encCb(self,msg):
        self.zero=msg.data
    def execute(self,data):
        rospy.sleep(self.delay)
        if self.zero<=self.count:
            self.p.publish(self.speed)
            return 'id'
        else:
            self.off.publish()
            return 'next'

class M1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.s=rospy.Subscriber('/motor1/zero',Int16,self.encCb)
        self.p=rospy.Publisher('/motor1/motor',Int16)
        self.off=rospy.Publisher('/motor1/off',Empty)
        self.zero=0

        global speed
        self.speed=speed
        global count
        self.count=count
        global delay
        self.delay=delay

    def encCb(self,msg):
        self.zero=msg.data
    def execute(self,data):
        rospy.sleep(self.delay)
        if self.zero<=self.count:
            self.p.publish(self.speed)
            return 'id'
        else:
            self.off.publish()
            return 'next'

class M3(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.subscriber=rospy.Subscriber('/motor3/zero',Int16,self.encCb)
        self.p=rospy.Publisher('/motor3/motor',Int16)
        self.off=rospy.Publisher('/motor3/off',Empty)
        self.zero=0

        global speed
        self.speed=speed
        global count
        self.count=count
        global delay
        self.delay=delay

    def encCb(self,msg):
        self.zero=msg.data
    def execute(self,data):
        rospy.sleep(self.delay)
        if self.zero<=self.count:
            self.p.publish(self.speed)
            return 'id'
        else:
            self.off.publish()
            return 'next'

class Reset(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.r0=rospy.Publisher('/motor0/reset',Empty)
        self.r1=rospy.Publisher('/motor1/reset',Empty)
        self.r2=rospy.Publisher('/motor2/reset',Empty)
        self.r3=rospy.Publisher('/motor3/reset',Empty)
    def execute(self,data):
        self.r0.publish()
        self.r1.publish()
        self.r2.publish()
        self.r3.publish()
        rospy.sleep(0.5)
        return 'next'


class All(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.s0=rospy.Subscriber('/motor0/zero',Int16,self.Cb0)
        self.s1=rospy.Subscriber('/motor1/zero',Int16,self.Cb1)
        self.s2=rospy.Subscriber('/motor2/zero',Int16,self.Cb2)
        self.s3=rospy.Subscriber('/motor3/zero',Int16,self.Cb3)
        self.z0=0
        self.z1=0
        self.z2=0
        self.z3=0
        self.p0=rospy.Publisher('/motor0/motor',Int16)
        self.off0=rospy.Publisher('/motor0/off',Empty)
        self.p1=rospy.Publisher('/motor1/motor',Int16)
        self.off1=rospy.Publisher('/motor1/off',Empty)
        self.p2=rospy.Publisher('/motor2/motor',Int16)
        self.off2=rospy.Publisher('/motor2/off',Empty)
        self.p3=rospy.Publisher('/motor3/motor',Int16)
        self.off3=rospy.Publisher('/motor3/off',Empty)

        global speed
        self.speed=speed
        global count
        self.count=count-10
        global delay
        self.delay=delay

    def Cb0(self,msg):
        self.z0=msg.data
    def Cb1(self,msg):
        self.z1=msg.data
    def Cb2(self,msg):
        self.z2=msg.data
    def Cb3(self,msg):
        self.z3=msg.data
    def execute(self,data):
        rospy.sleep(self.delay)
        if self.z0<=self.count or self.z1<=self.count or self.z2<=self.count or self.z3<=self.count:
            if self.z0<=self.count:
                self.p0.publish(self.speed)
            else:
                self.off0.publish()

            if self.z1<=self.count:
                self.p1.publish(self.speed)
            else:
                self.off1.publish()

            if self.z2<=self.count:
                self.p2.publish(self.speed)
            else:
                self.off2.publish()

            if self.z3<=self.count:
                self.p3.publish(self.speed)
            else:
                self.off3.publish()
            return 'id'
        else:
            self.off0.publish()
            self.off1.publish()
            self.off2.publish()
            self.off3.publish()
            return 'next'


class main():
    rospy.init_node('easy_walk')
    sm=smach.StateMachine(outcomes=['outcomes'])

    with sm:
        smach.StateMachine.add('INIT',Init(),
                transitions={'id':'INIT','next':'SET'})
        smach.StateMachine.add('SET',Set(),
                transitions={'id':'SET','next':'MOTOR3'})
        smach.StateMachine.add('MOTOR3',M3(),
                transitions={'id':'MOTOR3','next':'MOTOR1'})
        smach.StateMachine.add('MOTOR1',M1(),
                transitions={'id':'MOTOR1','next':'MOTOR2'})
        smach.StateMachine.add('MOTOR2',M2(),
                transitions={'id':'MOTOR2','next':'MOTOR0'})
        smach.StateMachine.add('MOTOR0',M0(),
                transitions={'id':'MOTOR0','next':'RESET'})
        smach.StateMachine.add('RESET',Reset(),
                transitions={'id':'RESET','next':'ALL'})
        smach.StateMachine.add('ALL',All(),
                transitions={'id':'ALL','next':'SET'})
        #0->2->1->3
        #smach.StateMachine.add('SET',Set(),
        #        transitions={'id':'SET','next':'MOTOR0'})
        #smach.StateMachine.add('MOTOR0',M0(),
        #        transitions={'id':'MOTOR0','next':'MOTOR2'})
        #smach.StateMachine.add('MOTOR2',M2(),
        #        transitions={'id':'MOTOR2','next':'MOTOR1'})
        #smach.StateMachine.add('MOTOR1',M1(),
        #        transitions={'id':'MOTOR1','next':'MOTOR3'})
        #smach.StateMachine.add('MOTOR3',M3(),
        #        transitions={'id':'MOTOR3','next':'RESET'})
        #smach.StateMachine.add('RESET',Reset(),
        #        transitions={'id':'RESET','next':'ALL'})
        #smach.StateMachine.add('ALL',All(),
        #        transitions={'id':'ALL','next':'SET'})
    

    sis=smach_ros.IntrospectionServer('server_name',sm,'/SM_ROOT')
    sis.start()

    outcome=sm.execute()
    rospy.spin()

if __name__ == '__main__':
    main()
