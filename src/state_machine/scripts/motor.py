#!/usr/bin/env python

import rospy
import smach
import smach_ros
from std_msgs.msg import Int32

enc_node=rospy.get_param('enc_node','enc0')
motor_node=rospy.get_param('motor_node','motor0')
motorcon_node=rospy.get_param('motorcon_node','motorcon0')

speed=0

class Init(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.subscriber=rospy.Subscriber(motorcon_node,Int32,self.motorconCb)
        self.subscriber=rospy.Subscriber(enc_node,Int32,self.motorconCb)
    def motorconCb(self,msg):
        global speed
        self.speed=msg.data
        speed=self.speed
    def execute(self,data):
        rospy.sleep(0.2)
        global speed
        if speed==0:
            return 'id'
        else:
            speed=self.speed
            return 'next'

class Diff(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome2'])
    def execute(self,data):
        rospy.sleep(1)
        return 'outcome2'

class Count(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome3'])
    def execute(self,data):
        global speed
        print(speed)
        speed=0
        rospy.sleep(1)
        return 'outcome3'

class main():
    rospy.init_node('motor_move')
    sm=smach.StateMachine(outcomes=['outcome4'])

    with sm:
        smach.StateMachine.add('INIT',Init(),
                transitions={'id':'INIT','next':'DIFF'})
        smach.StateMachine.add('DIFF',Diff(),
                transitions={'outcome2':'COUNT'})
        smach.StateMachine.add('COUNT',Count(),
                transitions={'outcome3':'INIT'})

    sis=smach_ros.IntrospectionServer('server_name',sm,'/SM_ROOT')
    sis.start()

    outcome=sm.execute()
    rospy.spin()

if __name__ == '__main__':
    main()
