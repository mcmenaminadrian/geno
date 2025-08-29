// creature.hpp

class Creature {

    private:
        bool fullyRecessive;
        bool Astate;
        bool Bstate;


    public:
        Creature(bool A, bool B): Astate(A), Bstate(B)
            {fullyRecessive = Astate & Bstate;};
        bool isFullyRecessive(){return fullyRecessive;}
        bool isPartiallyRecessive(){ return (Astate|Bstate) & !isFullyRecessive();}
        bool getAState(){return Astate;}
        bool getBState(){return Bstate;}
};