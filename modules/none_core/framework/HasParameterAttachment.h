#ifndef FRAMEWORK_HASPARAMETERATTACHMENT_H
#define FRAMEWORK_HASPARAMETERATTACHMENT_H

namespace none {
    class HasParameterAttachment {
    protected:
        virtual void initParameterAttachment() = 0;
        virtual void onClientParameterUpdate(float newValue) = 0;
        bool _isAttached = false;
    public:
        std::function<void(float)> getClientParameterUpdateCallback(){
            return [this](float newValue){
                onClientParameterUpdate(newValue);
            };
        }

        /// Sets attached to true
        void setIsAttached(){
            _isAttached = true;
        }
        bool isAttached() const{
            return _isAttached;
        }
    };
}

#endif //FRAMEWORK_HASPARAMETERATTACHMENT_H
