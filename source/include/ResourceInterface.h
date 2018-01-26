#ifndef RESOURCEINTERFACE_H
#define RESOURCEINTERFACE_H


class ResourceInterface
{
    public:
        ResourceInterface();
        virtual ~ResourceInterface();
        virtual long Usage() = 0;
    protected:
        //unsigned Useage;
    private:
};

#endif // RESOURCEINTERFACE_H
