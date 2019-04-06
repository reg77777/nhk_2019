#!/usr/bin/env python

import rospy
import smach
import smach_ros

class Foo(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1','outcome2'])

    def execute(self,data):
        rospy.loginfo('state is init')
        rospy.sleep(1)
        return 'outcome1'

class Bar(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1'])

    def execute(self,data):
        rospy.loginfo('state is start')
        rospy.sleep(1)
        return 'outcome1'

class init(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=[''])

class wait(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=[''])

class walk(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=[''])

class main():
    rospy.init_node('state_machine')

    sm=smach.StateMachine(outcomes=['outcome4'])

    with sm:
        smach.StateMachine.add('FOO',Foo(),
                               transitions={'outcome1':'BAR', 'outcome2':'outcome4'})
        smach.StateMachine.add('BAR',Bar(),
                               transitions={'outcome1':'FOO'})

    sis = smach_ros.IntrospectionServer('server_name',sm,'/SM_ROOT')
    sis.start()

    outcome=sm.execute()
    rospy.spin()

if __name__ == '__main__':
    main()
