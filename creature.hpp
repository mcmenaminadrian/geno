// creature.hpp

class Creature {

    private:
        bool fullyRecessive;
        bool Astate;
        bool Bstate;


    public:
        Creature(bool A, bool B): Astate(A), Bstate(B)
            {fullyRecessive = Astate & Bstate;};
        bool isFullyRecessive() const {return fullyRecessive;}
        bool isPartiallyRecessive() const { return (Astate|Bstate) & !isFullyRecessive();}
        bool getAState() const {return Astate;}
        bool getBState() const {return Bstate;}
};