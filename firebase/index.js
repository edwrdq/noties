const fs = require('fs');   
const { initializeApp } = require("firebase/app");
const { getFirestore, doc, getDoc, setDoc } = require("firebase/firestore");
const { authenticateUser } = require("./auth");

const firebaseConfig = {
    apiKey: "apikey",
    authDomain: "authdomain",
    projectId: "projectID",
    storageBucket: "storagebucket",
    messagingSenderId: "messagingcenterid",
    appId: "appid"
};

const app = initializeApp(firebaseConfig);
const db = getFirestore(app);

let userId = null;

async function checkFlag(uid) {

    if (!userId) {
        console.log('user not authenticated, aborting process!');
        return false;
    }

    const flagRef = doc(db, "users", userId, "cloudUsage");
    const flagSnap = await getDoc(flagRef);

    if (flagSnap.exists()) {
        const { flag } = flagSnap.data();
        fs.writeFileSync('flag.txt', flag.toString(), 'utf-8');
        console.log(`downloaded firestore flag: ${flag} !`);
        return flag === true;
    } else {
        console.log("no firestore flag found, aborting");
        return false;
    }

}


function readLocalFlag() {
    try{
        const flag = fs.readFileSync('flag.txt', 'utf-8').trim();
        if (flag === 'false') {
            console.log('local flag is false. aborting...');
            return false;
        } else if (flag === 'true') {
            console.log('local flag is true, continuing.');
            return true;
        } else {
            console.log('unexpected content in file. treating as invalid');
            return null;
        }
    } catch (err) {
        console.log('No local flag file found, checking firestore...')
        return null;
    }
}

async function uploadNotes() {
    if (!userID) {
        console.log("user not authenticated. cannot upload note.");
        return;
    }

    const noteRef = doc(db, "users", userID, "notes", noteId);
    await setDoc(noteRef, { content: noteContent, timestamp: new Date() });
    console.log('note uploaded succesfully');
}

function readUserId() {
    try {
        const userId = fs.readFileSync('userId.txt', 'utf-8').trim();
        if (userId) {
            return userId;
        }
    } catch (err) {
        console.log("no user id found, authenticating");
        return null;
    }
}

function readNoteContent(filePath) {
    try {
        const content = fs.readFileSync(filePath, 'utf-8');
        return content;
    } catch (err) {
        console.error("error reading note file:", err);
        return null;
    }
}

async function main(filePath) {
    const noteId = path.basename(filePath);
    const noteContent = readNoteContent(filePath);

    if (!noteContent) {
        console.log("no content found in note file, aborting");
        return;
    }

    const localFlag = readLocalFlag()

    if (localFlag === false) return;

    if (localFlag === null) {
        const firestoreFlag = await checkFlag(userId);
        if (!firestoreFlag) return;
    }

    await uploadNotes(noteId, noteContent);
}

(async () => {

    const filePath = process.argv[2];

    userId = readUserId();
    if (!userId) {
        userId = await authenticateUser();
        if (!userId) {
            console.log("auth failed, exiting");
            return;
        }
        fs.writeFileSync('userId.txt', userId, 'utf-8');
    }

    main(filePath);
})();





