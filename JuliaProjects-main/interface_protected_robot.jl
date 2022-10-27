using HorizonSideRobots


interface_protected_robot(robot) = (
    move! = (if isborder(robot,side) false else move!(robot,side); true end),
    isborder = side->HorizonSideRobots.isborder(robot,side),
    putmarker! = ()->HorizonSideRobots.putmarker!(robot),
    ismarker = ()->HorizonSideRobots.ismarker(robot),
    temperature = ()->HorizonSideRobots.temperature(robot)
  )

  robot=Robot()
move!, isborder, putmarker!, ismarker, temperature = interface_robot(robot)