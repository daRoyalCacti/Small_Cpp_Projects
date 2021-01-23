//https://eigen.tuxfamily.org/dox/modules.html
#include <iostream>


#include <Eigen/Dense>

#define EIGEN_USE_MKL_ALL   //https://eigen.tuxfamily.org/dox/TopicUsingIntelMKL.html
                            //https://eigen.tuxfamily.org/dox/TopicUsingBlasLapack.html

int main() {
    Eigen::MatrixXd m(2,2);    //matrix of size 2x2 with double precision elements
                                    //https://eigen.tuxfamily.org/dox/group__QuickRefPage.html#QuickRef_Types

    //filling the matrix
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << "matrix with elements naively set\n" << m << std::endl;

    //run time random matrix
    Eigen::MatrixXd m2 = Eigen::MatrixXd::Random(3,3);
    //transforming the matrix to be between 10, 110
    m2 = (m2 + Eigen::MatrixXd::Constant(3,3,1.2)) * 50;    //Constant(a,b,c) gives an axb martrix with all elements c

    //compile time random matrix
    Eigen::Matrix3d m3 = Eigen::Matrix3d::Random(); //matrix3d -> 3x3 matrix will all elements double precision
    m3 = (m3 + Eigen::Matrix3d::Constant(1.2)) * 50;

    //run time vector
    Eigen::VectorXd v(3); //3 for a vector of size 3 (column vector)
    v << 1, 2, 3;   //v = (1,2,3)

    //compile time vector
    Eigen::Vector3d v1(1,2,3);

    //matrix multiplication
    std::cout << "\nMultiplication of random matrix with (1,2,3)'\nRuntime:\n" << m2*v << "\nCompile time:\n" << m3*v1 << std::endl;

    //matrix of strange size known at compile time (5,4)
    Eigen::Matrix<int, 5, 4> m4 = Eigen::MatrixXi::Random(5,4);
    std::cout << "\nMatrix of int type with size 5x4 known at compile time\n" << m4 << std::endl;




    //https://eigen.tuxfamily.org/dox/TopicUsingBlasLapack.html
    std::cout << "\nSome operations changed by defining EIGEN_USE_MKL_ALL\nhttps://eigen.tuxfamily.org/dox/TopicUsingIntelMKL.html" << std::endl;
    //lu decomposition
    std::cout << "\nlu decomposition\n" << m3.lu().solve(v1) << std::endl;

    //transpose
    std::cout << "\nTranspose\n" << m2.transpose() << std::endl;

    Eigen::MatrixXd test(2,2);    //matrix of size 2x2 with double precision elements
    //https://eigen.tuxfamily.org/dox/group__QuickRefPage.html#QuickRef_Types

    //filling the matrix
    test(0,0) = 3;
    test(1,0) = 2.5;
    test(0,1) = -1;
    test(1,1) = 1.5;
            //eigenvalue and eigenvector solving
    Eigen::EigenSolver<Eigen::MatrixXd> es(test); //solving for matrix m
    if (es.info() != Eigen::Success) {
        std::cout << "Eigen solver failed" << std::endl;
    } else {
        std::cout << "\nUsing a real value solver" << std::endl;
        std::cout << "Eigen values :\n" << es.eigenvalues() << std::endl;
        std::cout << "Eigen vectors (each column is an eigenvector) :\n" << es.eigenvectors() << std::endl;
        std::cout << "Values in brackets represent complex numbers. a+bi = (a,b)" << std::endl;
    }

    //sine of a vector
    std::cout << "\ntaking sin() of a vector\n" << v1.array().sin() << std::endl;

    //squaring a matrix
    std::cout << "\nsquaring a matrix\n" << m2.array().square() << std::endl;

    //sqrt of a matrix
    std::cout << "\nsqrt of a matrix\n" << m3.array().sqrt() << std::endl;

}

