# Student Management System

A simple console‑based C++ application for managing student records and course enrollments with GPA tracking.

---

## Description

This Student Management System lets users add, update, and remove students, enroll students in courses, calculate GPAs, and display course‑centric reports showing students and average grades. Data is saved to and loaded from a text file for persistence between runs.

It demonstrates basic object‑oriented programming concepts including classes, inheritance, vectors, file handling, and modular design.

---

## Motivation

I built this project to practice C++ object‑oriented programming and to create a useful student/course management tool with real‑world functionality such as GPA calculation and course reporting.

---

## Problem Solved

Before this project, managing student information and course grades required manual tracking. This system automates:
- student record keeping
- course enrollment
- grade tracking
- GPA calculation  
and provides a structured, menu‑driven interface.

---

## Installation

### Requirements
- A C++ compiler (e.g., `g++`)
- Windows, macOS, or Linux terminal

### Compile the project

Run this command in the project directory:

```bash
C++ main.cpp student.cpp course.cpp person.cpp -o student_system
