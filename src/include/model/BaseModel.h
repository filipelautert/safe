#ifndef _BASEMODEL_H_
#define _BASEMODEL_H_

class BaseModel
{
  private:
    char *now();

  protected:
    char *createdAt, *updatedAt;
    int id;

    void setUpdatedAt();
    void setCreatedAt();

  public:
    BaseModel();
    virtual ~BaseModel();
    char *getCreatedAt();
    char *getUpdatedAt();
    int getId();

    virtual void populateFromCharArray(const char *r) = 0;
    virtual char *toCharArray() = 0;
};

#endif