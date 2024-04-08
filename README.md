# Pricing Asian Options on AWS Graviton Processors

In this repository, we price a certain type of Exotic option known as a Path-Dependent Asian in C++ using Monte Carlo Methods according to the code here https://www.quantstart.com/articles/Asian-option-pricing-with-C-via-Monte-Carlo-Methods/.

AWS Graviton is a family of processors designed to deliver the best price performance for your cloud workloads running in Amazon Elastic Compute Cloud (Amazon EC2).

We use a Crow, a C++ framework for exposing the application via a webservice. https://github.com/CrowCpp/Crow

We provide a Dockerfile to containerise the application.


