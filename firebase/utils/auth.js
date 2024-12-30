const { getAuth, signInWithEmailAndPassword } = require("firebase/auth");


async function authenticateUser() {
    const auth = getAuth();
    const email = "userinput";
    const password = "userinput";

    try {
        const userCredential = await signInWithEmailAndPassword(auth, email, password);
        console.log("user signed in:", userCredential.user.uid);
        return userCredential.user.uid;
    } catch (error) {
        console.log("error signing in!");
        return null;
    }
}

module.exports = { authenticateUser };