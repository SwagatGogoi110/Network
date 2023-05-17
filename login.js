import { initializeApp } from "https://www.gstatic.com/firebasejs/9.6.10/firebase-app.js";
import { getAuth, signInWithEmailAndPassword } from "https://www.gstatic.com/firebasejs/9.6.10/firebase-auth.js";

const firebaseConfig = {
    apiKey: "AIzaSyDdIRkmxITAUK6JdWGkmhaIKqNCMbmxsf4",
    authDomain: "network-975df.firebaseapp.com",
    projectId: "network-975df",
    storageBucket: "network-975df.appspot.com",
    messagingSenderId: "263056727358",
    appId: "1:263056727358:web:470dc5d344f12985dee06f"
};

const app = initializeApp(firebaseConfig);
const auth = getAuth(app);


document.getElementById("login-form").addEventListener('submit', (e) => {

    e.preventDefault();

    var email = document.getElementById('email').value;
    var password = document.getElementById('password').value;

    signInWithEmailAndPassword(auth, email, password)
        .then((userCredential) => {
            // Signed in 
            const user = userCredential.user;
            window.location.href = "nextpage.html";
            // ...
        })
        .catch((error) => {
            alert("Error signing in : User Not Found");
        });    
});
