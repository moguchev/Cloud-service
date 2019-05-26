class AbstractReceiver {
public:
    virtual ~AbstractReceiver() = default;
};

class Receiver : public AbstractReceiver{
public:
    ~Receiver() override = default;
};