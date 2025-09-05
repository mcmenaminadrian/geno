// creature.hpp

class Creature {

    private:
        bool Astate;
        bool Bstate;


    public:
        Creature(const bool A, const bool B): Astate(A), Bstate(B) {}
        bool isFullyRecessive() const {return Astate & Bstate;}
        bool isPartiallyRecessive() const { return (Astate|Bstate) & !isFullyRecessive();}
        bool getAState() const {return Astate;}
        bool getBState() const {return Bstate;}
};

