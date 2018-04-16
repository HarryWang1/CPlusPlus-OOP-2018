
#include <iostream>
#include <vector>
using namespace std;


class Instrument {
public:
    virtual void makeSound() const =0;
private:
};

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}

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
};

class Trombone : public Brass {
public:
    Trombone(unsigned size) : Brass(size) {}
};

class Percussion : public Instrument {
public:
    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};
class Drum : public Percussion {};
class Cymbal : public Percussion {};

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
};

class Cello : public String {
public:
    Cello(unsigned pitch) : String(pitch) {}
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

// PART ONE
int main() {

    cout << "Define some instruments ----------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
    Mill mill;
  
    cout << "Put the instruments into the MILL ------------------------------\n";
    mill.receiveInstrument(trpt);
    mill.receiveInstrument(violin);
    mill.receiveInstrument(tbone);
    mill.receiveInstrument(drum);
    mill.receiveInstrument(cello);
    mill.receiveInstrument(cymbal);
  
    cout << "Daily test -----------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians-------------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());-----------------------\n";
    groucho.testPlay();	
    cout << endl;
    groucho.acceptInstrument(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    groucho.testPlay();	
    cout << endl;
    mill.receiveInstrument(*groucho.giveBackInstrument());
    harpo.acceptInstrument(mill.loanOut());
    groucho.acceptInstrument(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ----------\n";
  
    // // fifth
    mill.receiveInstrument(*groucho.giveBackInstrument());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstrument(*harpo.giveBackInstrument());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;

}

