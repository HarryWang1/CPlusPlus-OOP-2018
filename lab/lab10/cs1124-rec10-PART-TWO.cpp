#include <iostream>
#include <vector>
using namespace std;


class Instrument {
public:
    virtual void makeSound() const =0;
    virtual void play() const =0;
private:
};

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}

//Brass is still an abstract class because it doesn't define play(). 
class Brass : public Instrument {   
public:
    Brass(unsigned size) : size(size) {}

    void makeSound() const override {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << size << endl;
    }
private:
    unsigned size;
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned size) : Brass(size) {}
    void play() const {
        cout << "Toot";
    }
};

class Trombone : public Brass {
public:
    Trombone(unsigned size) : Brass(size) {}
    void play() const {
        cout << "Blat";
    }
};

class Percussion : public Instrument {
public:
    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};
class Drum : public Percussion {
public:
    void play() const {
        cout << "Boom";
    }
};
class Cymbal : public Percussion {
public:    
    void play() const {
        cout << "Crash";
    }
};

class String : public Instrument {
public:
    String(unsigned pitch) : pitch(pitch) {}

    void makeSound() const override {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
};

class Violin : public String {
public:
    Violin(unsigned pitch) : String(pitch) {}
    void play() const {
        cout << "Screech";
    }
};

class Cello : public String {
public:
    Cello(unsigned pitch) : String(pitch) {}
    void play() const {
        cout << "Squawk";
    }
};

class Musician {
public:
    Musician() : instrument(nullptr) {}

    void acceptInstrument(Instrument* instPtr) { 
        instrument = instPtr; 
    }

    Instrument* giveBackInstrument() { 
        Instrument* result(instrument); 
        instrument = nullptr;
        return result;
    }

    void testPlay() const {
        if (instrument != nullptr) {
            instrument->makeSound(); 
        } else {
            cerr << "have no instrument\n";
        }
    }

    void play() const {
        if (instrument != nullptr) {
            instrument->play(); 
        }
    }

private:
    Instrument* instrument;
};

class Mill {
public:
    void dailyTestPlay() {
        for (Instrument* instrument : instruments) {
            //only test existing instruments
            if (instrument != nullptr) {
                instrument->makeSound();
            }
        }
    }
    void receiveInstrument(Instrument& instrument) {
        instrument.makeSound();
        Instrument* instrumentPointer = &instrument;
        //look for empty space first. If no empty space, add to the end.
        for (size_t i=0; i<instruments.size(); i++) {
            if (instruments[i] == nullptr) {
                instruments[i] = instrumentPointer;
                return;
            }
        }
        instruments.push_back(instrumentPointer);
    }
    Instrument* loanOut() {
        //find the first available instrument
        for (size_t i=0; i<instruments.size(); i++) {
            if (instruments[i] != nullptr) {
                Instrument* save = instruments[i];
                instruments[i] = nullptr;
                return save;
            }
        }
        //return nullptr if no available instruments
        return nullptr;
    }
private:
    vector<Instrument* > instruments;
};

class Orchestra {
public:
    void play() const {
        for (Musician* musician : musicians) {
            musician->play();
        }
        cout << endl;
    }
    void addPlayer(Musician& musician) {
        Musician* pointer = &musician;
        //maximum size of the orchestra is 25 players
        if (musicians.size() < 25) {
            musicians.push_back(pointer);
        }
    }
private:
    vector<Musician* > musicians;
};


// PART TWO
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    Mill mill;
    mill.receiveInstrument(trpt);
    mill.receiveInstrument(violin);
    mill.receiveInstrument(tbone);
    mill.receiveInstrument(drum);
    mill.receiveInstrument(cello);
    mill.receiveInstrument(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orchestra orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstrument(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstrument(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstrument(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstrument(*ralph.giveBackInstrument());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstrument(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstrument(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstrument(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstrument(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main

