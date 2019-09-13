// Generated by gencpp from file messages/VictorOut.msg
// DO NOT EDIT!


#ifndef MESSAGES_MESSAGE_VICTOROUT_H
#define MESSAGES_MESSAGE_VICTOROUT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace messages
{
template <class ContainerAllocator>
struct VictorOut_
{
  typedef VictorOut_<ContainerAllocator> Type;

  VictorOut_()
    : deviceID(0)
    , busVoltage(0.0)
    , outputVoltage(0.0)
    , outputPercent(0.0)  {
    }
  VictorOut_(const ContainerAllocator& _alloc)
    : deviceID(0)
    , busVoltage(0.0)
    , outputVoltage(0.0)
    , outputPercent(0.0)  {
  (void)_alloc;
    }



   typedef int32_t _deviceID_type;
  _deviceID_type deviceID;

   typedef float _busVoltage_type;
  _busVoltage_type busVoltage;

   typedef float _outputVoltage_type;
  _outputVoltage_type outputVoltage;

   typedef float _outputPercent_type;
  _outputPercent_type outputPercent;





  typedef boost::shared_ptr< ::messages::VictorOut_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::messages::VictorOut_<ContainerAllocator> const> ConstPtr;

}; // struct VictorOut_

typedef ::messages::VictorOut_<std::allocator<void> > VictorOut;

typedef boost::shared_ptr< ::messages::VictorOut > VictorOutPtr;
typedef boost::shared_ptr< ::messages::VictorOut const> VictorOutConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::messages::VictorOut_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::messages::VictorOut_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace messages

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/lunar/share/std_msgs/cmake/../msg'], 'messages': ['/home/nvidia/SoftwareDevelopment/ROS/src/messages/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::messages::VictorOut_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::messages::VictorOut_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::messages::VictorOut_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::messages::VictorOut_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::messages::VictorOut_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::messages::VictorOut_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::messages::VictorOut_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1308269e2bd460ac3f55ed9f4bcd8d51";
  }

  static const char* value(const ::messages::VictorOut_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1308269e2bd460acULL;
  static const uint64_t static_value2 = 0x3f55ed9f4bcd8d51ULL;
};

template<class ContainerAllocator>
struct DataType< ::messages::VictorOut_<ContainerAllocator> >
{
  static const char* value()
  {
    return "messages/VictorOut";
  }

  static const char* value(const ::messages::VictorOut_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::messages::VictorOut_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 deviceID\n\
float32 busVoltage\n\
float32 outputVoltage\n\
float32 outputPercent\n\
";
  }

  static const char* value(const ::messages::VictorOut_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::messages::VictorOut_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.deviceID);
      stream.next(m.busVoltage);
      stream.next(m.outputVoltage);
      stream.next(m.outputPercent);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VictorOut_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::messages::VictorOut_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::messages::VictorOut_<ContainerAllocator>& v)
  {
    s << indent << "deviceID: ";
    Printer<int32_t>::stream(s, indent + "  ", v.deviceID);
    s << indent << "busVoltage: ";
    Printer<float>::stream(s, indent + "  ", v.busVoltage);
    s << indent << "outputVoltage: ";
    Printer<float>::stream(s, indent + "  ", v.outputVoltage);
    s << indent << "outputPercent: ";
    Printer<float>::stream(s, indent + "  ", v.outputPercent);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MESSAGES_MESSAGE_VICTOROUT_H
