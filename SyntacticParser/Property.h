
#pragma once
/*
 ����װ����
 ������ֵ�����÷��ʹ��ˣ�get��set
*/
template<class T>
class Property {
public:
    typedef T(*Getter)(const T&);
    typedef void (*Setter)(T&);

#pragma region ���캯��
    /*
     ������ֵ������get������set����
     ������ṩ���򲻶Է��ʽ��й���
    */
    Property(T& value, Getter getter = nullptr, Setter setter = nullptr)
        : _value(value), _getter(getter), _setter(setter) {}
    /*
     ������ֵ������get������set����
     ������ṩ���򲻶Է��ʽ��й���
    */
    Property(T& value, Setter setter)
        : _value(value), _getter(nullptr), _setter(setter) {}
#pragma endregion
    
    /*
     ���Ե�Get����
    */
    T Get() const {
        if (_getter)
            return _getter(_value);
        else
            return _value;
    }
    /*
     ���Ե�Set����
    */
    void Set(T value) {
        if (_setter)
            _setter(_value);
        else
            _value = value;
    }

private:
    T& _value;          // �󶨵�����ֵ
    Getter _getter;     // get�ķ���
    Setter _setter;     // set�ķ���
};

/*
 ֻ������װ����
 ������ֵ�����÷��ʹ��ˣ�get
*/
template<class T>
class ROProperty {

public:
    typedef T(*Getter)(const T&);
    typedef void (*Setter)(T&);
    /*
     ������ֵ������get����
     ������ṩ���򲻶Է��ʽ��й���
    */
    ROProperty(T& value, Getter getter = nullptr)
        : _value(value), _getter(getter) {}
    /*
     ���Ե�Get����
    */
    T Get() const {
        if (_getter)
            return _getter(_value);
        else
            return _value;
    }
private:
    T& _value;          // �󶨵�����ֵ
    Getter _getter;     // get�ķ���
};
