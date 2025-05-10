#pragma once

class IEntity 
{
public:

    virtual int getId() const = 0;

    virtual void setId(int id) = 0;

    virtual ~IEntity() = default;

};
