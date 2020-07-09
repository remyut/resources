import 'package:flutter/material.dart';

void main() {
  runApp(
    MaterialApp(
      home: Scaffold(
        backgroundColor: Colors.blue[400],
        body: Center(
          child: Image(
            image: AssetImage('images/birds.jpg'),
          ),
        ),
        appBar: AppBar(
          backgroundColor: Colors.blue[400],
          title: Text('The sky is blue everywhere'),
        ),
      ),
    ),
  );
}
